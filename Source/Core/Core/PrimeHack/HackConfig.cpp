#include "HackConfig.h"

#include <array>
#include <string>

#include "Common/IniFile.h"

#include "Core/PrimeHack/PrimeUtils.h"
#include "Core/PrimeHack/EmuVariableManager.h"

#include "Core/PrimeHack/Mods/AutoEFB.h"
#include "Core/PrimeHack/Mods/CutBeamFxMP1.h"
#include "Core/PrimeHack/Mods/DisableBloom.h"
#include "Core/PrimeHack/Mods/FpsControls.h"
#include "Core/PrimeHack/Mods/RestoreDashing.h"
#include "Core/PrimeHack/Mods/Invulnerability.h"
#include "Core/PrimeHack/Mods/Noclip.h"
#include "Core/PrimeHack/Mods/SkipCutscene.h"
#include "Core/PrimeHack/Mods/SpringballButton.h"
#include "Core/PrimeHack/Mods/ViewModifier.h"
#include "Core/PrimeHack/Mods/ContextSensitiveControls.h"
#include "Core/PrimeHack/Mods/FriendVouchers.h"
#include "Core/PrimeHack/Mods/PortalSkipMP2.h"
#include "Core/PrimeHack/Mods/DisableHudMemoPopup.h"
#include "Core/PrimeHack/Mods/ElfModLoader.h"

#include "Core/HW/Wiimote.h"
#include "Core/HW/WiimoteEmu/WiimoteEmu.h"
#include "Core/HW/GCPad.h"
#include "Core/ConfigManager.h"
#include "Core/Config/GraphicsSettings.h"

#include "InputCommon/ControllerInterface/ControllerInterface.h"
#include "InputCommon/InputConfig.h"

#include "VideoCommon/VideoConfig.h"
#include "Core\HW\GCPadEmu.h"

namespace prime {
namespace {
std::array<float, 4> sensitivity;
std::array<float, 4> cursor_sensitivity;
std::array<float, 4> camera_fov;

std::array<bool, 4> inverted_x = {false, false, false, false};
std::array<bool, 4> inverted_y = {false, false, false, false};
std::array<bool, 4> scale_cursor_sens = {false, false, false, false};
HackManager hack_mgr;
AddressDB addr_db;
EmuVariableManager var_mgr;
bool is_running = false;
CameraLock lock_camera = CameraLock::Unlocked;
std::array<bool, 4> reticle_lock = {false, false, false, false};

std::string pending_modfile = "";
bool mod_suspended = false;
}

void InitializeHack() {
  if (is_running) return; is_running = true;
  PrimeMod::set_hack_manager(GetHackManager());
  PrimeMod::set_address_database(GetAddressDB());
  init_db(*GetAddressDB());

  // Create all mods
  hack_mgr.add_mod("auto_efb", std::make_unique<AutoEFB>());
  hack_mgr.add_mod("cut_beam_fx_mp1", std::make_unique<CutBeamFxMP1>());
  hack_mgr.add_mod("disable_bloom", std::make_unique<DisableBloom>());
  hack_mgr.add_mod("fps_controls", std::make_unique<FpsControls>());
  hack_mgr.add_mod("invulnerability", std::make_unique<Invulnerability>());
  hack_mgr.add_mod("noclip", std::make_unique<Noclip>());
  hack_mgr.add_mod("skip_cutscene", std::make_unique<SkipCutscene>());
  hack_mgr.add_mod("restore_dashing", std::make_unique<RestoreDashing>());
  hack_mgr.add_mod("springball_button", std::make_unique<SpringballButton>());
  hack_mgr.add_mod("fov_modifier", std::make_unique<ViewModifier>());
  hack_mgr.add_mod("context_sensitive_controls", std::make_unique<ContextSensitiveControls>());
  hack_mgr.add_mod("portal_skip_mp2", std::make_unique<PortalSkipMP2>());
  hack_mgr.add_mod("friend_vouchers_cheat", std::make_unique<FriendVouchers>());
  hack_mgr.add_mod("disable_hudmemo_popup", std::make_unique<DisableHudMemoPopup>());
  hack_mgr.add_mod("elf_mod_loader", std::make_unique<ElfModLoader>());

  hack_mgr.enable_mod("skip_cutscene");
  hack_mgr.enable_mod("fov_modifier");

  // Enable no PrimeHack control mods
  if (!SConfig::GetInstance().bEnablePrimeHack) {
    return;
  }

  hack_mgr.enable_mod("fps_controls");
  hack_mgr.enable_mod("springball_button");
  hack_mgr.enable_mod("context_sensitive_controls");
  hack_mgr.enable_mod("elf_mod_loader");
}

bool CheckBeamCtl(int beam_num, int player_index) {
  return Wiimote::CheckBeam(beam_num);
}

bool CheckVisorCtl(int visor_num, int player_index) {
  return Wiimote::CheckVisor(visor_num);
}

bool CheckVisorScrollCtl(bool direction, int player_index) {
  return Wiimote::CheckVisorScroll(direction);
}

bool CheckBeamScrollCtl(bool direction, int player_index) {
  return Wiimote::CheckBeamScroll(direction);
}

bool CheckSpringBallCtl(int player_index) {
  return Wiimote::CheckSpringBall(player_index);
}

bool ImprovedMotionControls() {
  return Wiimote::CheckImprovedMotions();
}
  
bool CheckForward(int player_index) {
  return Wiimote::CheckForward();
}

bool CheckBack(int player_index) {
  return Wiimote::CheckBack();
}

bool CheckLeft(int player_index) {
  return Wiimote::CheckLeft();
}

bool CheckRight(int player_index) {
  return Wiimote::CheckRight();
}

bool CheckJump(int player_index) {
  return Wiimote::CheckJump();
}

bool CheckGrappleCtl() {
  return Wiimote::CheckGrapple();
}

bool GrappleTappingMode() {
  return Wiimote::UseGrappleTapping();
}

bool GrappleCtlBound() {
  return Wiimote::GrappleCtlBound();
}

void SetEFBToTexture(bool toggle) {
  return Config::SetCurrent(Config::GFX_HACK_SKIP_EFB_COPY_TO_RAM, toggle);
}

bool UseMPAutoEFB() {
  return Config::Get(Config::AUTO_EFB);
}

bool LockCameraInPuzzles() {
  return Config::Get(Config::LOCKCAMERA_IN_PUZZLES);
}

bool GetNoclip() {
  return SConfig::GetInstance().bPrimeNoclip;
}

bool GetInvulnerability() {
  return SConfig::GetInstance().bPrimeInvulnerability;
}

bool GetSkipCutscene() {
  return SConfig::GetInstance().bPrimeSkipCutscene;
}

bool GetRestoreDashing() {
  return SConfig::GetInstance().bPrimeRestoreDashing;
}

bool GetEFBTexture() {
  return Config::Get(Config::GFX_HACK_SKIP_EFB_COPY_TO_RAM);
}

bool GetBloom() {
  return Config::Get(Config::DISABLE_BLOOM);
}

bool GetEnableSecondaryGunFX() {
  return Config::Get(Config::ENABLE_SECONDARY_GUNFX);
}

bool GetShowGCCrosshair() {
  return Config::Get(Config::GC_SHOW_CROSSHAIR);
}

u32 GetGCCrosshairColor() {
  return Config::Get(Config::GC_CROSSHAIR_COLOR_RGBA);
}

bool GetAutoArmAdjust() {
  return Config::Get(Config::ARMPOSITION_MODE) == 0;
}

bool GetToggleArmAdjust() {
  return Config::Get(Config::TOGGLE_ARM_REPOSITION);
}

std::tuple<float, float, float> GetArmXYZ() {
  float x = Config::Get(Config::ARMPOSITION_LEFTRIGHT) / 100.f;
  float y = Config::Get(Config::ARMPOSITION_FORWARDBACK) / 100.f;
  float z = Config::Get(Config::ARMPOSITION_UPDOWN) / 100.f;

  return std::make_tuple(x, y, z);
}

void UpdateHackSettings(int player_index) {
  double camera, cursor;
  bool invertx, inverty, scale_sens = false, lock = false;

  if (hack_mgr.get_active_game() >= Game::PRIME_1_GCN) {
    std::tie(camera, cursor, invertx, inverty) =
      static_cast<GCPad*>(Pad::GetConfig()->GetController(player_index))->GetPrimeSettings();
  } else {
    std::tie(camera, cursor, invertx, inverty, scale_sens, lock) =
      static_cast<WiimoteEmu::Wiimote*>(Wiimote::GetConfig()->GetController(player_index))->GetPrimeSettings();
  }

  SetSensitivity((float)camera, player_index);
  SetCursorSensitivity((float)cursor, player_index);
  SetInvertedX(invertx, player_index);
  SetInvertedY(inverty, player_index);
  SetScaleCursorSensitivity(scale_sens, player_index);
  SetReticleLock(lock, player_index);
}

float GetSensitivity(int player_index) {
  return sensitivity[player_index];
}

void SetSensitivity(float sens, int player_index) {
  sensitivity[player_index] = sens;
}

bool HandleReticleLockOn(int player_index)
{
  return reticle_lock[player_index];
}

void SetReticleLock(bool lock, int player_index)
{
  reticle_lock[player_index] = lock;
}

float GetCursorSensitivity(int player_index) {
  return cursor_sensitivity[player_index];
}

void SetCursorSensitivity(float sens, int player_index) {
  cursor_sensitivity[player_index] = sens;
}

float GetFov() {
  return Config::Get(Config::FOV);
}

bool InvertedY(int player_index) {
  return inverted_y[player_index];
}

void SetInvertedY(bool inverted, int player_index) {
  inverted_y[player_index] = inverted;
}

bool InvertedX(int player_index) {
  return inverted_x[player_index];
}

void SetInvertedX(bool inverted, int player_index) {
  inverted_x[player_index] = inverted;
}

bool ScaleCursorSensitivity(int player_index) {
  return scale_cursor_sens[player_index];
}

void SetScaleCursorSensitivity(bool scale, int player_index) {
  scale_cursor_sens[player_index] = scale;
}

bool CheckPitchRecentre(int player_index) {
  if (hack_mgr.get_active_game() >= Game::PRIME_1_GCN) {
    if (Pad::PrimeUseController()) {
      return Pad::CheckPitchRecentre();
    } 
  }
  else if (Wiimote::PrimeUseController()) {
    return Wiimote::CheckPitchRecentre(player_index);
  }

  return false;
}

double GetHorizontalAxis(int player_index) {
  if (hack_mgr.get_active_game() >= Game::PRIME_1_GCN) {
    if (Pad::PrimeUseController()) {
      return std::get<0>(Pad::GetPrimeStickXY());
    } 
  }
  else if (Wiimote::PrimeUseController()) {
    return std::get<0>(Wiimote::GetPrimeStickXY(player_index));
  } 
  
  return static_cast<double>(g_mouse_input->GetDeltaHorizontalAxis());
}

double GetVerticalAxis(int player_index) {
  if (hack_mgr.get_active_game() >= Game::PRIME_1_GCN) {
    if (Pad::PrimeUseController()) {
      return std::get<1>(Pad::GetPrimeStickXY());
    } 
  }
  else if (Wiimote::PrimeUseController()) {
    return std::get<1>(Wiimote::GetPrimeStickXY(player_index));
  } 

  return static_cast<double>(g_mouse_input->GetDeltaVerticalAxis());
}

bool GetCulling() {
  return Config::Get(Config::TOGGLE_CULLING);
}

void SetLockCamera(CameraLock lock) {
  lock_camera = lock;
}

CameraLock GetLockCamera() {
  return lock_camera;
}

std::tuple<bool, bool> GetMenuOptions() {
  return Wiimote::GetBVMenuOptions();
}

AddressDB* GetAddressDB() {
  return &addr_db;
}

EmuVariableManager* GetVariableManager() {
  return &var_mgr;
}

HackManager* GetHackManager() {
  return &hack_mgr;
}

bool ModPending() {
  return !pending_modfile.empty();
}

void ClearPendingModfile() {
  pending_modfile.clear();
}

std::string GetPendingModfile() {
  return pending_modfile;
}

void SetPendingModfile(std::string const& path) {
  pending_modfile = path;
}

bool ModSuspended() {
  return mod_suspended;
}

void SuspendMod() {
  mod_suspended = true;
}

void ResumeMod() {
  mod_suspended = false;
}
}  // namespace prime
