// --------------------------------------------------------------------------------------
// Die Deckenkrabbler
//
// krabbelt an der Decke entlang bis er auf eine (Gegner) Wand stösst und dreht dann um
// Schiesst in gleichen Abständen auf den Boden
// Hat Speed == Value2 und SchussDelay == Value1
// --------------------------------------------------------------------------------------

#include "Gegner_KrabblerOben.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerKrabblerOben::GegnerKrabblerOben(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::LAUFEN;
    Energy = 75;
    Value1 = Wert1;
    Value2 = Wert2;
    xSpeed = static_cast<float>(Value2);
    BlickRichtung = DirectionEnum::LINKS;
    ShotDelay = static_cast<float>(Value1);
    AnimSpeed = 0.5f;
    AnimStart = 0;
    AnimEnde = 9;
    ChangeLight = Light;
    Destroyable = true;
}

// --------------------------------------------------------------------------------------
// "Bewegungs KI"

void GegnerKrabblerOben::DoKI() {
    BlickRichtung = DirectionEnum::LINKS;
    SimpleAnimation();

    // An der Seitenwand umdrehen
    if (blockl & BLOCKWERT_WAND || blockl & BLOCKWERT_GEGNERWAND) {
        xSpeed = static_cast<float>(Value2);
        BlickRichtung = DirectionEnum::RECHTS;
    }

    if (blockr & BLOCKWERT_WAND || blockr & BLOCKWERT_GEGNERWAND) {
        xSpeed = static_cast<float>(-Value2);
        BlickRichtung = DirectionEnum::LINKS;
    }

    // Schuss Delay verzögern
    ShotDelay -= Timer.sync(1.0f);

    // Je nach Handlung richtig verhalten
    switch (Handlung) {
        case GEGNER::LAUFEN:  // Krabbler krabbelt an der Decke entlang
        {
            // Schiessen ?
            if (ShotDelay <= 0.0f) {
                ShotDelay = static_cast<float>(Value1);
                Handlung = GEGNER::SCHIESSEN;
                Projectiles.PushProjectile(xPos + 24.0f, yPos + 48.0f, KRABBLERLASER1);
                PartikelSystem.PushPartikel(xPos - 1.0f, yPos + 44.0f, LASERFLAME);
                SoundManager.PlayWave3D(static_cast<int>(xPos + 25.0f),
                                        static_cast<int>(yPos + 37.0f), 44100, SOUND::LASERSHOT);
                AnimPhase = 10;
                AnimEnde = 14;
                AnimStart = 0;
                AnimSpeed = 0.75f;
            }
        } break;

        case GEGNER::SCHIESSEN: {
            // Fertig mit schiessen ?
            if (AnimPhase == AnimStart) {
                AnimEnde = 9;
                AnimPhase = 0;
                AnimSpeed = 0.5f;
                Handlung = GEGNER::LAUFEN;
            }
        } break;

        default:
            break;
    }  // switch
}

// --------------------------------------------------------------------------------------
// DeckenKrabbler explodiert
// --------------------------------------------------------------------------------------

void GegnerKrabblerOben::GegnerExplode() {
    // Explosion
    for (int i = 0; i < 5; i++)
        PartikelSystem.PushPartikel(xPos - 15.0f + static_cast<float>(GetRandom(20)),
                                    yPos - 15.0f + static_cast<float>(GetRandom(40)), EXPLOSION_MEDIUM3);

    SoundManager.PlayWave(100, 128, -GetRandom(2000) + 11025, SOUND::EXPLOSION1);  // Sound ausgeben

    Player[0].Score += 300;
}
