#pragma once

#include <memory>
#include <vector>

#include "Core/PrimeHack/HackManager.h"
#include "Core/PrimeHack/AddressDB.h"
#include "Core/PrimeHack/EmuVariableManager.h"

#include "InputCommon/ControlReference/ControlReference.h"

// Naming scheme will match dolphin as this place acts as an interface between the hack & dolphin proper
namespace prime {
void InitializeHack();

bool CheckBeamCtl(int beam_num, int player_index = 0);
bool CheckVisorCtl(int visor_num, int player_index = 0);
bool CheckBeamScrollCtl(bool direction, int player_index = 0);
bool CheckVisorScrollCtl(bool direction, int player_index = 0);
bool CheckSpringBallCtl(int player_index = 0);
bool ImprovedMotionControls();
bool CheckForward(int player_index = 0);
bool CheckBack(int player_index = 0);
bool CheckLeft(int player_index = 0);
bool CheckRight(int player_index = 0);
bool CheckJump(int player_index = 0);

bool CheckGrappleCtl();
bool GrappleTappingMode();
bool GrappleCtlBound();

void SetEFBToTexture(bool toggle);
bool UseMPAutoEFB();
bool LockCameraInPuzzles();
bool GetEFBTexture();
bool GetBloom();

bool GetNoclip();
bool GetInvulnerability();
bool GetSkipCutscene();
bool GetRestoreDashing();

bool GetEnableSecondaryGunFX();
bool GetShowGCCrosshair();
u32 GetGCCrosshairColor();

bool GetAutoArmAdjust();
bool GetToggleArmAdjust();
std::tuple<float, float, float> GetArmXYZ();

void UpdateHackSettings(int player_index = 0);

float GetSensitivity(int player_index = 0);
void SetSensitivity(float sensitivity, int player_index = 0);
float GetCursorSensitivity(int player_index = 0);
void SetCursorSensitivity(float sensitivity, int player_index = 0);
bool ScaleCursorSensitivity(int player_index = 0);
void SetScaleCursorSensitivity(bool scale, int player_index = 0);
float GetFov();
bool InvertedY(int player_index = 0);
void SetInvertedY(bool inverted, int player_index = 0);
bool InvertedX(int player_index = 0);
void SetInvertedX(bool inverted, int player_index = 0);
bool GetCulling();

bool HandleReticleLockOn(int player_index = 0);
void SetReticleLock(bool lock, int player_index = 0);

enum CameraLock { Centre, Angle45, Unlocked };

void SetLockCamera(CameraLock lock);
CameraLock GetLockCamera();

bool CheckPitchRecentre(int player_index = 0);

double GetHorizontalAxis(int player_index = 0);
double GetVerticalAxis(int player_index = 0);

std::tuple<bool, bool> GetMenuOptions();

HackManager *GetHackManager();
AddressDB *GetAddressDB();
EmuVariableManager *GetVariableManager();

bool ModPending();
void ClearPendingModfile();
std::string GetPendingModfile();
void SetPendingModfile(std::string const& path);

bool ModSuspended();
void SuspendMod();
void ResumeMod();
}
