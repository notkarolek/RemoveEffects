#include <mod/amlmod.h>
#include <mod/config.h>

#include <dlfcn.h>

MYMODCFG(net.notkarolek.removeeffects, RemoveEffects, 1.1, notkarolek)

struct Group { const char* key; const char* const* symbols; };

static const char* const BIRDS[]         = { "_ZN6CBirds6RenderEv", 0 };
static const char* const CLOUDS[]        = { "_ZN7CClouds6RenderEv", "_ZN7CClouds22RenderBottomFromHeightEv", "_ZN7CClouds22VolumetricCloudsRenderEv", 0 };
static const char* const PLANE_TRAILS[]  = { "_ZN12CPlaneTrails6RenderEv", "_ZN11CPlaneTrail6RenderEf", 0 };
static const char* const BROKEN_GLASS[]  = { "_ZN17CFallingGlassPane6RenderEv", "_ZN6CGlass6RenderEv", 0 };
static const char* const POST_EFFECTS[]  = { "_ZN12CPostEffects6RenderEv", 0 };
static const char* const SKIDMARKS[]     = { "_ZN10CSkidmarks6RenderEv", 0 };
static const char* const MOTION_BLUR[]   = { "_ZN18CMotionBlurStreaks6RenderEv", "_ZN27CRegisteredMotionBlurStreak6RenderEv", 0 };
static const char* const BULLET_TRACES[] = { "_ZN13CBulletTraces6RenderEv", 0 };
static const char* const BRIGHT_LIGHTS[] = { "_ZN13CBrightLights6RenderEv", 0 };
static const char* const MIRRORS[]       = { "_ZN8CMirrors17RenderReflectionsEv", 0 };
static const char* const CORONAS[]       = { "_ZN8CCoronas6RenderEv", "_ZN8CCoronas17RenderReflectionsEv", "_ZN8CCoronas19RenderSunReflectionEv", 0 };
static const char* const SHADOWS[]       = { "_ZN8CShadows19RenderStoredShadowsEb", "_ZN8CShadows19RenderStaticShadowsEb", "_ZN8CShadows24RenderExtraPlayerShadowsEv", 0 };
static const char* const PARTICLES[]     = { "_ZN11FxManager_c6RenderEP8RwCamerah", 0 };
static const char* const RAIN[]          = { "_ZN8CWeather17RenderRainStreaksEv", 0 };
static const char* const LIGHT_FOG[]     = { "_ZN12CPointLights15RenderFogEffectEv", 0 };
static const char* const LAMP_LIGHTS[]   = { "_ZN7CEntity22ProcessLightsForEntityEv", 0 };
static const char* const HEADLIGHTS[]    = { "_ZN8CVehicle15DoHeadLightBeamEiR7CMatrixh", "_ZN8CVehicle21DoHeadLightReflectionER7CMatrixjhh", 0 };
static const char* const SUN_GLARE[]     = { "_ZN8CVehicle10DoSunGlareEv", 0 };
static const char* const SEARCHLIGHTS[]  = { "_ZN5CHeli25RenderAllHeliSearchLightsEv", "_ZN11CTheScripts21RenderAllSearchLightsEv", 0 };
static const char* const WATER[]         = { "_ZN11CWaterLevel14RenderWaterFogEv", "_ZN11CWaterLevel15RenderBoatWakesEv", 0 };

static const Group GROUPS[] = {
    { "birds", BIRDS },
    { "clouds", CLOUDS },
    { "plane_trails", PLANE_TRAILS },
    { "broken_glass", BROKEN_GLASS },
    { "post_effects", POST_EFFECTS },
    { "skidmarks", SKIDMARKS },
    { "motion_blur", MOTION_BLUR },
    { "bullet_traces", BULLET_TRACES },
    { "bright_lights", BRIGHT_LIGHTS },
    { "mirror_reflections", MIRRORS },
    { "coronas", CORONAS },
    { "shadows", SHADOWS },
    { "particles", PARTICLES },
    { "rain", RAIN },
    { "light_fog", LIGHT_FOG },
    { "lamp_lights", LAMP_LIGHTS },
    { "headlight_beams", HEADLIGHTS },
    { "sun_glare", SUN_GLARE },
    { "searchlights", SEARCHLIGHTS },
    { "water_effects", WATER },
};

#ifdef __aarch64__
static const unsigned char RETURN[4] = { 0xC0, 0x03, 0x5F, 0xD6 };
#else
static const unsigned char RETURN[4] = { 0x70, 0x47, 0x00, 0xBF };
#endif

ON_MOD_LOAD()
{
    void* game = dlopen("libGTASA.so", RTLD_NOW | RTLD_NOLOAD);
    if (!game || !aml) return;

    for (const Group& g : GROUPS) {
        if (!cfg->GetBool(g.key, false, "Effects")) continue;
        for (const char* const* sym = g.symbols; *sym; sym++) {
            uintptr_t fn = (uintptr_t)dlsym(game, *sym) & ~(uintptr_t)1;
            if (fn) aml->Write(fn, (uintptr_t)RETURN, sizeof(RETURN));
        }
    }
}
