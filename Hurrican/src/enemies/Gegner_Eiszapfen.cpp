// --------------------------------------------------------------------------------------
// Der Eiszapfen
//
// hängt faul an der Decke und fällt runter, wenn der Hurri drunter vorbeikommt
// --------------------------------------------------------------------------------------

#include "Gegner_Eiszapfen.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerEiszapfen::GegnerEiszapfen(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::STEHEN;
    Energy = 100;
    ChangeLight = Light;
    Destroyable = false;
    Value1 = Wert1;
    Value2 = Wert2;

    // schon vorher runterfallen? (bei Eisfaust Boss)
    //
    if (Value1 == 1.0f) {
        Handlung = GEGNER::FALLEN;
        ySpeed = 30.0f;
        yAcc = 5.0f;

        SoundManager.PlayWave(100, 128, 11025 + GetRandom(2000), SOUND::STONEFALL);
    }
}

// --------------------------------------------------------------------------------------
// "Bewegungs KI"
// --------------------------------------------------------------------------------------

void GegnerEiszapfen::DoKI() {
    SimpleAnimation();

    switch (Handlung) {
        case GEGNER::STEHEN: {
            if (pAim->ypos > yPos &&
                pAim->xpos + 35.0f > xPos + 10.0f - 60.0f &&
                pAim->xpos + 35.0f < xPos + 10.0f + 60.0f) {
                Handlung = GEGNER::FALLEN;
                ySpeed = 30.0f;
                yAcc = 5.0f;

                SoundManager.PlayWave(100, 128, 11025 + GetRandom(2000), SOUND::STONEFALL);

                for (int i = 0; i < 15; i++) {
                    PartikelSystem.PushPartikel(xPos - 20.0f + static_cast<float>(GetRandom(35)),
                                                yPos - 10.0f + static_cast<float>(GetRandom(20)), WATERFLUSH2);
                    PartikelSystem.PushPartikel(xPos - 20.0f + static_cast<float>(GetRandom(35)),
                                                yPos - 10.0f + static_cast<float>(GetRandom(20)), SMOKE);
                }
            }
        } break;

        case GEGNER::FALLEN: {
            if (ySpeed > 40.0f) {
                ySpeed = 40.0f;
                yAcc = 0.0f;
            }

            if (blocku & BLOCKWERT_WAND)
                Energy = 0.0f;

        } break;

        default:
            break;
    }  // switch

    // Testen, ob der Spieler den Zapfen berührt hat
    TestDamagePlayers(30.0f, true);
}

// --------------------------------------------------------------------------------------
// Eiszapfen explodiert
// --------------------------------------------------------------------------------------

void GegnerEiszapfen::GegnerExplode() {
    SoundManager.PlayWave(100, 128, 11025, SOUND::EXPLOSION1);

    for (int i = 0; i < 30; i++) {
        PartikelSystem.PushPartikel(xPos - 20.0f + static_cast<float>(GetRandom(35)),
                                    yPos - 10.0f + static_cast<float>(GetRandom(60)), WATERFLUSH2);
        PartikelSystem.PushPartikel(xPos - 20.0f + static_cast<float>(GetRandom(35)),
                                    yPos - 10.0f + static_cast<float>(GetRandom(60)), SMOKE);
    }

    Player[0].Score += 100;
}
