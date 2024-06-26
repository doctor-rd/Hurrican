// --------------------------------------------------------------------------------------
// Die fallende Bombe im Fahrstuhl
//
// fällt dem Hurri von oben auf die Birne
// --------------------------------------------------------------------------------------

#include "Gegner_FallBombe.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerFallBombe::GegnerFallBombe(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::NOTVISIBLE;
    Energy = 10;
    Value1 = Wert1;
    Value2 = Wert2;
    ChangeLight = Light;
    Destroyable = false;
    AnimEnde = 6;
    AnimStart = 0;
    AnimSpeed = 1.0f;
    ySpeed = 10.0f;
    yAcc = 3.0f;
    SmokeDelay = 0.0f;
    TestBlock = false;
}

// --------------------------------------------------------------------------------------
// "Bewegungs KI"
// --------------------------------------------------------------------------------------

void GegnerFallBombe::DoKI() {
    SimpleAnimation();

    switch (Handlung) {
        // Stein wird "aktiviert" (über den Hurri gesetzt damit er von dort runterfallen kann)
        case GEGNER::NOTVISIBLE: {
            Handlung = GEGNER::FALLEN;
            yPos -= RENDERHEIGHT + 59.0f;
            if (yPos < 0.0f)
                yPos = 0.0f;
        } break;

        // Stein fällt runter
        case GEGNER::FALLEN: {
            if (ySpeed > g_Fahrstuhl_Speed + 50.0f)
                ySpeed = g_Fahrstuhl_Speed + 50.0f;

            SmokeDelay -= Timer.sync(1.0f);

            if (SmokeDelay <= 0.0f) {
                SmokeDelay = 0.15f;
                PartikelSystem.PushPartikel(xPos - static_cast<float>(GetRandom(8)),
                                            yPos - 16.0f, SMOKE);
            }
        } break;

        default:
            break;
    }  // switch

    // Testen, ob der Spieler den Stein berührt hat
    TestDamagePlayers(25.0f, true);

    if (yPos >= g_Fahrstuhl_yPos - 59)
        Energy = 0.0f;
}

// --------------------------------------------------------------------------------------
// FallBombe explodiert
// --------------------------------------------------------------------------------------

void GegnerFallBombe::GegnerExplode() {
    SoundManager.PlayWave(100, 128, 8000 + GetRandom(4000), SOUND::EXPLOSION1);
    PartikelSystem.PushPartikel(xPos - 40.0f, yPos, EXPLOSION_BIG);

    for (int i = 0; i < 40; i++)
        PartikelSystem.PushPartikel(xPos + static_cast<float>(GetRandom(20)),
                                    yPos + 40.0f + static_cast<float>(GetRandom(30)), FUNKE);

    for (int i = 0; i < 16; i++)
        PartikelSystem.PushPartikel(xPos - 10.0f + static_cast<float>(GetRandom(30)),
                                    yPos + 40.0f + static_cast<float>(GetRandom(30)), SMOKE3);
}
