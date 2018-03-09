cmake_minimum_required(VERSION 3.9)
project(hurrican)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsingle-precision-constant -fno-rtti")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -flto")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -O2 -flto")
endif()

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${CMAKE_EXE_LINKER_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${CMAKE_EXE_LINKER_FLAGS}")

set(HURRICAN_SOURCES
        src/bosses/Boss_BigFish.cpp
        src/bosses/Boss_BigFish.hpp
        src/bosses/Boss_Bratklops.cpp
        src/bosses/Boss_Bratklops.hpp
        src/bosses/Boss_Drache.cpp
        src/bosses/Boss_Drache.hpp
        src/bosses/Boss_EisFaust.cpp
        src/bosses/Boss_EisFaust.hpp
        src/bosses/Boss_EvilHurri.cpp
        src/bosses/Boss_EvilHurri.hpp
        src/bosses/Boss_FahrstuhlBoss.cpp
        src/bosses/Boss_FahrstuhlBoss.hpp
        src/bosses/Boss_FlugBoss.cpp
        src/bosses/Boss_FlugBoss.hpp
        src/bosses/Boss_Golem.cpp
        src/bosses/Boss_Golem.hpp
        src/bosses/Boss_MetalHead.cpp
        src/bosses/Boss_MetalHead.hpp
        src/bosses/Boss_PharaoKopf.cpp
        src/bosses/Boss_PharaoKopf.hpp
        src/bosses/Boss_RiesenPiranha.cpp
        src/bosses/Boss_RiesenPiranha.hpp
        src/bosses/Boss_RiesenQualle.cpp
        src/bosses/Boss_RiesenQualle.hpp
        src/bosses/Boss_RiesenRaupe.cpp
        src/bosses/Boss_RiesenRaupe.hpp
        src/bosses/Boss_RiesenSpinne.cpp
        src/bosses/Boss_RiesenSpinne.hpp
        src/bosses/Boss_RiesenWespe.cpp
        src/bosses/Boss_RiesenWespe.hpp
        src/bosses/Boss_Rollmops.cpp
        src/bosses/Boss_Rollmops.hpp
        src/bosses/Boss_SchmidtOrgie.cpp
        src/bosses/Boss_SchmidtOrgie.hpp
        src/bosses/Boss_Schneekoenig.cpp
        src/bosses/Boss_Schneekoenig.hpp
        src/bosses/Boss_Skeletor.cpp
        src/bosses/Boss_Skeletor.hpp
        src/bosses/Boss_Skull.cpp
        src/bosses/Boss_Skull.hpp
        src/bosses/Boss_Spinnenmaschine.cpp
        src/bosses/Boss_Spinnenmaschine.hpp
        src/bosses/Boss_Stahlfaust.cpp
        src/bosses/Boss_Stahlfaust.hpp
        src/bosses/Boss_TheWall.cpp
        src/bosses/Boss_TheWall.hpp
        src/bosses/Boss_Ufo.cpp
        src/bosses/Boss_Ufo.hpp
        src/bosses/Boss_WuxeSpinnen.cpp
        src/bosses/Boss_WuxeSpinnen.hpp
        src/cml/cml/core/meta/common.h
        src/cml/cml/core/meta/if.h
        src/cml/cml/core/meta/switch.h
        src/cml/cml/core/cml_assert.h
        src/cml/cml/core/cml_meta.h
        src/cml/cml/core/common.h
        src/cml/cml/core/dynamic_1D.h
        src/cml/cml/core/dynamic_2D.h
        src/cml/cml/core/external_1D.h
        src/cml/cml/core/external_2D.h
        src/cml/cml/core/fixed_1D.h
        src/cml/cml/core/fixed_2D.h
        src/cml/cml/core/fwd.h
        src/cml/cml/et/array_promotions.h
        src/cml/cml/et/scalar_ops.h
        src/cml/cml/et/scalar_promotions.h
        src/cml/cml/et/size_checking.h
        src/cml/cml/et/tags.h
        src/cml/cml/et/traits.h
        src/cml/cml/mathlib/checking.h
        src/cml/cml/mathlib/coord_conversion.h
        src/cml/cml/mathlib/epsilon.h
        src/cml/cml/mathlib/frustum.h
        src/cml/cml/mathlib/helper.h
        src/cml/cml/mathlib/interpolation.h
        src/cml/cml/mathlib/mathlib.h
        src/cml/cml/mathlib/matrix_basis.h
        src/cml/cml/mathlib/matrix_concat.h
        src/cml/cml/mathlib/matrix_misc.h
        src/cml/cml/mathlib/matrix_ortho.h
        src/cml/cml/mathlib/matrix_projection.h
        src/cml/cml/mathlib/matrix_rotation.h
        src/cml/cml/mathlib/matrix_transform.h
        src/cml/cml/mathlib/matrix_translation.h
        src/cml/cml/mathlib/misc.h
        src/cml/cml/mathlib/picking.h
        src/cml/cml/mathlib/projection.h
        src/cml/cml/mathlib/quaternion_basis.h
        src/cml/cml/mathlib/quaternion_rotation.h
        src/cml/cml/mathlib/typedef.h
        src/cml/cml/mathlib/vector_angle.h
        src/cml/cml/mathlib/vector_misc.h
        src/cml/cml/mathlib/vector_ortho.h
        src/cml/cml/mathlib/vector_transform.h
        src/cml/cml/matrix/class_ops.h
        src/cml/cml/matrix/determinant.h
        src/cml/cml/matrix/dynamic.h
        src/cml/cml/matrix/external.h
        src/cml/cml/matrix/fixed.h
        src/cml/cml/matrix/inverse.h
        src/cml/cml/matrix/lu.h
        src/cml/cml/matrix/matop_macros.h
        src/cml/cml/matrix/matrix_comparison.h
        src/cml/cml/matrix/matrix_expr.h
        src/cml/cml/matrix/matrix_functions.h
        src/cml/cml/matrix/matrix_mul.h
        src/cml/cml/matrix/matrix_ops.h
        src/cml/cml/matrix/matrix_print.h
        src/cml/cml/matrix/matrix_promotions.h
        src/cml/cml/matrix/matrix_rowcol.h
        src/cml/cml/matrix/matrix_traits.h
        src/cml/cml/matrix/matrix_transpose.h
        src/cml/cml/matrix/matrix_unroller.h
        src/cml/cml/matvec/matvec_mul.h
        src/cml/cml/matvec/matvec_promotions.h
        src/cml/cml/quaternion/conjugate.h
        src/cml/cml/quaternion/inverse.h
        src/cml/cml/quaternion/quaternion.h
        src/cml/cml/quaternion/quaternion_comparison.h
        src/cml/cml/quaternion/quaternion_dot.h
        src/cml/cml/quaternion/quaternion_expr.h
        src/cml/cml/quaternion/quaternion_functions.h
        src/cml/cml/quaternion/quaternion_mul.h
        src/cml/cml/quaternion/quaternion_ops.h
        src/cml/cml/quaternion/quaternion_print.h
        src/cml/cml/quaternion/quaternion_promotions.h
        src/cml/cml/quaternion/quaternion_traits.h
        src/cml/cml/quaternion/quatop_macros.h
        src/cml/cml/vector/class_ops.h
        src/cml/cml/vector/dynamic.h
        src/cml/cml/vector/external.h
        src/cml/cml/vector/fixed.h
        src/cml/cml/vector/vecop_macros.h
        src/cml/cml/vector/vector_comparison.h
        src/cml/cml/vector/vector_expr.h
        src/cml/cml/vector/vector_functions.h
        src/cml/cml/vector/vector_ops.h
        src/cml/cml/vector/vector_print.h
        src/cml/cml/vector/vector_products.h
        src/cml/cml/vector/vector_promotions.h
        src/cml/cml/vector/vector_traits.h
        src/cml/cml/vector/vector_unroller.h
        src/cml/cml/cml.h
        src/cml/cml/constants.h
        src/cml/cml/defaults.h
        src/cml/cml/dynamic.h
        src/cml/cml/external.h
        src/cml/cml/fixed.h
        src/cml/cml/matrix.h
        src/cml/cml/quaternion.h
        src/cml/cml/util.h
        src/cml/cml/vector.h
        src/SDLPort/cfbo.cpp
        src/SDLPort/cfbo.h
        src/SDLPort/cshader.cpp
        src/SDLPort/cshader.h
        src/SDLPort/keymap.h
        src/SDLPort/opengl.h
        src/SDLPort/SDL_fmod.cpp
        src/SDLPort/SDL_fmod.h
        src/SDLPort/SDL_port.cpp
        src/SDLPort/SDL_port.h
        src/SDLPort/texture.cpp
        src/SDLPort/texture.h
        src/CCracktro.cpp
        src/CCracktro.hpp
        src/CCutScene.cpp
        src/CCutScene.hpp
        src/CDragonHack.cpp
        src/CDragonHack.hpp
        src/CGegner.hpp
        src/Console.cpp
        src/Console.hpp
        src/creditStrings.hpp
        src/DataStructures.hpp
        src/DX8Enum.cpp
        src/DX8Enum.hpp
        src/DX8Font.cpp
        src/DX8Font.hpp
        src/DX8Graphics.cpp
        src/DX8Graphics.hpp
        src/DX8Input.cpp
        src/DX8Input.hpp
        src/DX8Joystick.cpp
        src/DX8Joystick.hpp
        src/DX8Sound.cpp
        src/DX8Sound.hpp
        src/DX8Sprite.cpp
        src/DX8Sprite.hpp
        src/DX8Texture.cpp
        src/DX8Texture.hpp
        src/Gameplay.cpp
        src/Gameplay.hpp
        src/Gegner_Auge.cpp
        src/Gegner_Auge.hpp
        src/Gegner_BallerDrone.cpp
        src/Gegner_BallerDrone.hpp
        src/Gegner_BigRocket.cpp
        src/Gegner_BigRocket.hpp
        src/Gegner_BlueBoulder.cpp
        src/Gegner_BlueBoulder.hpp
        src/Gegner_BrockelRock.cpp
        src/Gegner_BrockelRock.hpp
        src/Gegner_Climber.cpp
        src/Gegner_Climber.hpp
        src/Gegner_DeckenKrabbe.cpp
        src/Gegner_DeckenKrabbe.hpp
        src/Gegner_Deckenturm.cpp
        src/Gegner_Deckenturm.hpp
        src/Gegner_Diamant.cpp
        src/Gegner_Diamant.hpp
        src/Gegner_Drone.cpp
        src/Gegner_Drone.hpp
        src/Gegner_EierMann.cpp
        src/Gegner_EierMann.hpp
        src/Gegner_EisStachel.cpp
        src/Gegner_EisStachel.hpp
        src/Gegner_Eiszapfen.cpp
        src/Gegner_Eiszapfen.hpp
        src/Gegner_Extras.cpp
        src/Gegner_Extras.hpp
        src/Gegner_FallBombe.cpp
        src/Gegner_FallBombe.hpp
        src/Gegner_FallingRock.cpp
        src/Gegner_FallingRock.hpp
        src/Gegner_FetteRakete.cpp
        src/Gegner_FetteRakete.hpp
        src/Gegner_FetteSpinne.cpp
        src/Gegner_FetteSpinne.hpp
        src/Gegner_FieseDrone.cpp
        src/Gegner_FieseDrone.hpp
        src/Gegner_FieserFireWalker.cpp
        src/Gegner_FieserFireWalker.hpp
        src/Gegner_FieserWalker.cpp
        src/Gegner_FieserWalker.hpp
        src/Gegner_FireSpider.cpp
        src/Gegner_FireSpider.hpp
        src/Gegner_Fledermaus.cpp
        src/Gegner_Fledermaus.hpp
        src/Gegner_FlugKanone.cpp
        src/Gegner_FlugKanone.hpp
        src/Gegner_Flugsack.cpp
        src/Gegner_Flugsack.hpp
        src/Gegner_Geschuetz.cpp
        src/Gegner_Geschuetz.hpp
        src/Gegner_GunTower.cpp
        src/Gegner_GunTower.hpp
        src/Gegner_Helper.cpp
        src/Gegner_Helper.hpp
        src/Gegner_Jaeger.cpp
        src/Gegner_Jaeger.hpp
        src/Gegner_Kettenglied.cpp
        src/Gegner_Kettenglied.hpp
        src/Gegner_KrabblerLinks.cpp
        src/Gegner_KrabblerLinks.hpp
        src/Gegner_KrabblerOben.cpp
        src/Gegner_KrabblerOben.hpp
        src/Gegner_KrabblerRechts.cpp
        src/Gegner_KrabblerRechts.hpp
        src/Gegner_KugelGross.cpp
        src/Gegner_KugelGross.hpp
        src/Gegner_KugelKlein.cpp
        src/Gegner_KugelKlein.hpp
        src/Gegner_KugelMedium.cpp
        src/Gegner_KugelMedium.hpp
        src/Gegner_KugelRiesig.cpp
        src/Gegner_KugelRiesig.hpp
        src/Gegner_LaFass.cpp
        src/Gegner_LaFass.hpp
        src/Gegner_LavaBall.cpp
        src/Gegner_LavaBall.hpp
        src/Gegner_LavaBallSpawner.cpp
        src/Gegner_LavaBallSpawner.hpp
        src/Gegner_LavaKrabbe.cpp
        src/Gegner_LavaKrabbe.hpp
        src/Gegner_Lavamann.cpp
        src/Gegner_Lavamann.hpp
        src/Gegner_Made.cpp
        src/Gegner_Made.hpp
        src/Gegner_Minidragon.cpp
        src/Gegner_Minidragon.hpp
        src/Gegner_MiniRocket.cpp
        src/Gegner_MiniRocket.hpp
        src/Gegner_MittelSpinne.cpp
        src/Gegner_MittelSpinne.hpp
        src/Gegner_Mutant.cpp
        src/Gegner_Mutant.hpp
        src/Gegner_Nest.cpp
        src/Gegner_Nest.hpp
        src/Gegner_NeuFisch.cpp
        src/Gegner_NeuFisch.hpp
        src/Gegner_OneUp.cpp
        src/Gegner_OneUp.hpp
        src/Gegner_PFlanze.cpp
        src/Gegner_Pflanze.hpp
        src/Gegner_Piranha.cpp
        src/Gegner_Piranha.hpp
        src/Gegner_PokeNuke.cpp
        src/Gegner_PokeNuke.hpp
        src/Gegner_PowerBlock.cpp
        src/Gegner_PowerBlock.hpp
        src/Gegner_Punisher.cpp
        src/Gegner_Punisher.hpp
        src/Gegner_Qualle.cpp
        src/Gegner_Qualle.hpp
        src/Gegner_Raketenwerfer.cpp
        src/Gegner_Raketenwerfer.hpp
        src/Gegner_ReitFlugsack.cpp
        src/Gegner_ReitFlugsack.hpp
        src/Gegner_RoboMan1.cpp
        src/Gegner_RoboMan1.hpp
        src/Gegner_RoboRaupe.cpp
        src/Gegner_RoboRaupe.hpp
        src/Gegner_Rotzpott.cpp
        src/Gegner_Rotzpott.hpp
        src/Gegner_Schabe.cpp
        src/Gegner_Schabe.hpp
        src/Gegner_SchienenViech.cpp
        src/Gegner_SchienenViech.hpp
        src/Gegner_SchleimAlien.cpp
        src/Gegner_SchleimAlien.hpp
        src/Gegner_SchleimBoller.cpp
        src/Gegner_SchleimBoller.hpp
        src/Gegner_SchleimMaul.cpp
        src/Gegner_SchleimMaul.hpp
        src/Gegner_Schneekoppe.cpp
        src/Gegner_Schneekoppe.hpp
        src/Gegner_Schwabbel.cpp
        src/Gegner_Schwabbel.hpp
        src/Gegner_SideRocket.cpp
        src/Gegner_SideRocket.hpp
        src/Gegner_SkiWalker.cpp
        src/Gegner_SkiWalker.hpp
        src/Gegner_SmallWespe.cpp
        src/Gegner_SmallWespe.hpp
        src/Gegner_SnowBomb.cpp
        src/Gegner_SnowBomb.hpp
        src/Gegner_SpiderBomb.cpp
        src/Gegner_SpiderBomb.hpp
        src/Gegner_Spitter.cpp
        src/Gegner_Spitter.hpp
        src/Gegner_Spitterbombe.cpp
        src/Gegner_Spitterbombe.hpp
        src/Gegner_Stachelbeere.cpp
        src/Gegner_Stachelbeere.hpp
        src/Gegner_Stahlmuecke.cpp
        src/Gegner_Stahlmuecke.hpp
        src/Gegner_Stalagtit.cpp
        src/Gegner_Stalagtit.hpp
        src/Gegner_StarBig.cpp
        src/Gegner_StarBig.hpp
        src/Gegner_StarSmall.cpp
        src/Gegner_StarSmall.hpp
        src/Gegner_StelzSack.cpp
        src/Gegner_StelzSack.hpp
        src/Gegner_Stuff.hpp
        src/Gegner_SwimWalker.cpp
        src/Gegner_SwimWalker.hpp
        src/Gegner_Walker.cpp
        src/Gegner_Walker.hpp
        src/Gegner_WandKannone.cpp
        src/Gegner_WandKannone.hpp
        src/Gegner_WandKrabbe.cpp
        src/Gegner_WandKrabbe.hpp
        src/Gegner_WasserMine.cpp
        src/Gegner_WasserMine.hpp
        src/Gegner_Zitrone.cpp
        src/Gegner_Zitrone.hpp
        src/GegnerClass.cpp
        src/GegnerClass.hpp
        src/GegnerPowerBlock.hpp
        src/GetKeyName.cpp
        src/GetKeyName.hpp
        src/Globals.hpp
        src/GUISystem.cpp
        src/GUISystem.hpp
        src/HUD.cpp
        src/HUD.hpp
        src/Intro.cpp
        src/Intro.hpp
        src/lightmap.cpp
        src/lightmap.hpp
        src/Logdatei.cpp
        src/Logdatei.hpp
        src/Main.cpp
        src/Main.hpp
        src/Mathematics.cpp
        src/Mathematics.hpp
        src/MemLeaks.hpp
        src/Menu.cpp
        src/Menu.hpp
        src/Outtro.cpp
        src/Outtro.hpp
        src/Partikelsystem.cpp
        src/Partikelsystem.hpp
        src/Player.cpp
        src/Player.hpp
        src/Projectiles.cpp
        src/Projectiles.hpp
        src/resource.hpp
        src/stdafx.cpp
        src/stdafx.hpp
        src/Texts.cpp
        src/Texts.hpp
        src/Tileengine.cpp
        src/Tileengine.hpp
        src/Timer.cpp
        src/Timer.hpp
        src/tracealloc.cpp
        src/Trigger_Bruecke.cpp
        src/Trigger_Bruecke.hpp
        src/Trigger_Column.cpp
        src/Trigger_Column.hpp
        src/Trigger_Column2.cpp
        src/Trigger_Column2.hpp
        src/Trigger_EndLevel.cpp
        src/Trigger_EndLevel.hpp
        src/Trigger_FadeMusic.cpp
        src/Trigger_FadeMusic.hpp
        src/Trigger_FahrStuhl.cpp
        src/Trigger_Fahrstuhl.hpp
        src/Trigger_Fass.cpp
        src/Trigger_Fass.hpp
        src/Trigger_Feuerspucker.cpp
        src/Trigger_Feuerspucker.hpp
        src/Trigger_Floating.cpp
        src/Trigger_Floating.hpp
        src/Trigger_Floating2.cpp
        src/Trigger_Floating2.hpp
        src/Trigger_Floating3.cpp
        src/Trigger_Floating3.hpp
        src/Trigger_Glubschi.cpp
        src/Trigger_Glubschi.hpp
        src/Trigger_Glubschi2.cpp
        src/Trigger_Glubschi2.hpp
        src/Trigger_LaFassSpawner.cpp
        src/Trigger_LaFassSpawner.hpp
        src/Trigger_Lift.cpp
        src/Trigger_Lift.hpp
        src/Trigger_LightFlare.cpp
        src/Trigger_LightFlare.hpp
        src/Trigger_LuefterGross.cpp
        src/Trigger_LuefterGross.hpp
        src/Trigger_LuefterKlein.cpp
        src/Trigger_LuefterKlein.hpp
        src/Trigger_LuefterKlein2.cpp
        src/Trigger_LuefterKlein2.hpp
        src/Trigger_Mushroom.cpp
        src/Trigger_Mushroom.hpp
        src/Trigger_PartikelSpawner.cpp
        src/Trigger_PartikelSpawner.hpp
        src/Trigger_Plattform.cpp
        src/Trigger_Plattform.hpp
        src/Trigger_Presse.cpp
        src/Trigger_Presse.hpp
        src/Trigger_Presswurst.cpp
        src/Trigger_Presswurst.hpp
        src/Trigger_SchleuseH.cpp
        src/Trigger_SchleuseH.hpp
        src/Trigger_SchleuseV.cpp
        src/Trigger_SchleuseV.hpp
        src/Trigger_Secret.cpp
        src/Trigger_Secret.hpp
        src/Trigger_ShootButton.cpp
        src/Trigger_ShootButton.hpp
        src/Trigger_ShootPlattform.cpp
        src/Trigger_ShootPlattform.hpp
        src/Trigger_Shrine.cpp
        src/Trigger_Shrine.hpp
        src/Trigger_SoundTrigger.cpp
        src/Trigger_SoundTrigger.hpp
        src/Trigger_Spikelift.cpp
        src/Trigger_Spikelift.hpp
        src/Trigger_Stampfstein.cpp
        src/Trigger_Stampfstein.hpp
        src/Trigger_SurfBrett.cpp
        src/Trigger_SurfBrett.hpp
        src/Trigger_Switch.cpp
        src/Trigger_Switch.hpp
        src/Trigger_Tube.cpp
        src/Trigger_Tube.hpp
        src/Trigger_TutorialText.cpp
        src/Trigger_TutorialText.hpp
        src/Trigger_Warning.cpp
        src/Trigger_Warning.hpp)

add_definitions(-DLINUX)
add_definitions(-DUSE_HOME_DIR)
add_definitions(-DUSE_GL2)
add_definitions(-DPLATFORM_SDL)
add_definitions(-DUSE_MODPLUG)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/SDLPort)
include_directories(${CMAKE_SOURCE_DIR}/src/cml)
add_executable(hurrican ${HURRICAN_SOURCES})

INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindSDL REQUIRED)
INCLUDE(FindSDL_mixer REQUIRED)
INCLUDE(FindSDL_image REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY} ${SDL_MIXER_LIBRARIES} ${SDL_IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} stdc++fs modplug)