// --------------------------------------------------------------------------------------
// Die Feuerspuckende Kletter Spinne
//
// Klettert hinten an der Wand rum und dreht sich in Richtung Hurri
// schiesst mit nem fiesen Flammenwerfer
// --------------------------------------------------------------------------------------

#include "Gegner_FireSpider.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerFireSpider::GegnerFireSpider(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::LAUFEN;
    Energy = 75;
    AnimSpeed = 0.75f;
    ChangeLight = Light;
    Destroyable = true;
    OwnDraw = true;
    AnimPhase = 0;
    AnimStart = 0;
    AnimEnde = 10;
    Value1 = Wert1;
    Value2 = Wert2;
    rot = 0.0f;
    shotdelay = 10.0f;
}

// --------------------------------------------------------------------------------------
// Eigene Draw Funktion
// --------------------------------------------------------------------------------------

void GegnerFireSpider::DoDraw() {
    // Spinne rendern
    //
    pGegnerGrafix[GegnerArt]->RenderSpriteRotated(xPos - TileEngine.XOffset,
                                                  yPos - TileEngine.YOffset, rot, AnimPhase,
                                                  0xFFFFFFFF);
}

// --------------------------------------------------------------------------------------
// "Bewegungs KI"
// --------------------------------------------------------------------------------------

void GegnerFireSpider::DoKI() {
    blocku = TileEngine.BlockUntenNormal(xPos, yPos, xPosOld, yPosOld, GegnerRect[GegnerArt]);
    SimpleAnimation();

    // Gegner auf Spieler ausrichten
    //

    // Abstände berechnen
    float dx = (xPos + 25.0f) - (pAim->xpos + 35.0f);
    float dy = (yPos + 18.0f) - (pAim->ypos + 40.0f);

    // Division durch Null verhinden
    if (dy == 0.0f)
        dy = 0.01f;

    // DKS - fixed uninitialized var warning:
    // float w, winkel;

    // DKS - converted to float, used new macros:
    // w = static_cast<float>(atan(dx / dy) * 360.0f / (D3DX_PI * 2));
    float w = RadToDeg(atanf(dx / dy));
    float winkel = w;

    if (dx >= 0.0f && dy >= 0.0f)
        winkel = w;
    else if (dx > 0.0f && dy < 0.0f)
        winkel = 180.0f + w;
    else if (dx < 0.0f && dy > 0.0f)
        winkel = 360.0f + w;
    else if (dx < 0.0f && dy < 0.0f)
        winkel = 180.0f + w;

    winkel = 360.0f - winkel;

    // Je nach Handlung richtig verhalten
    switch (Handlung) {
        case GEGNER::LAUFEN: {
            // Spinne rotieren
            //
            float inc = 5.0f;
            if (PlayerAbstand() > 150)
                inc = 8.0f;
            if (PlayerAbstand() > 250)
                inc = 12.0f;
            if (rot < winkel)
                rot += Timer.sync(inc);
            if (rot > winkel)
                rot -= Timer.sync(inc);

            if (PlayerAbstand() > 300)
                rot = winkel;

            // Spieler entsprechend verfolgen
            //
            if (PlayerAbstand() < 1000) {
                // DKS - Support new trig sin/cos lookup table and use deg/rad versions of sin/cos:
                // xSpeed = float ( sin(rot * D3DX_PI / 180.0f) * 7.5f);
                // ySpeed = float (-cos(rot * D3DX_PI / 180.0f) * 7.5f);
                xSpeed = sin_deg(rot) * 7.5f;
                ySpeed = -cos_deg(rot) * 7.5f;
            } else {
                xSpeed = 0;
                ySpeed = 0;
            }

            // Schusscounter unten und Blickwinkel in Richtung Spieler ?
            // Dann schiessen
            shotdelay -= Timer.sync(1.0f);

            if (shotdelay < 0.0f && abs(static_cast<int>(winkel - rot)) < 10 && PlayerAbstand() < 200) {
                shotdelay = 0.3f;
                Handlung = GEGNER::SCHIESSEN;
                AnimPhase = 11;
                AnimEnde = 11;
                AnimStart = 11;
                AnimCount = 0.0f;
                xSpeed = 0.0f;
                ySpeed = 0.0f;
            }
        } break;

        // ballern ?
        // solange, bis Hurri aus dem Schussfeld raus ist, oder der Counter abgelaufen ist
        //
        case GEGNER::SCHIESSEN: {
            shotdelay -= Timer.sync(1.0f);
            AnimCount += Timer.sync(1.0f);

            if (shotdelay <= 0.0f) {

                float xs = xPos + 8;
                float ys = yPos - 13;
                float r = 180.0f - rot;
                if (r < 0.0f)
                    r += 360.0f;

                // DKS - Support new trig sin/cos lookup table and use deg/rad versions of sin/cos:
                // r  = r * D3DX_PI / 180.0f;
                // xs = float (xs + sin (r) * 30.0f);
                // ys = float (ys + cos (r) * 30.0f);
                xs = xs + sin_deg(r) * 30.0f;
                ys = ys + cos_deg(r) * 30.0f;

                Projectiles.PushProjectile(xs, ys, SPIDERFIRE, pAim);
                shotdelay = 0.5f;
            }

            // Spieler nicht mehr im Schussfeld oder Schuss dauert schon eine Weile ?
            //
            if (abs(static_cast<int>(winkel - rot)) > 10 || PlayerAbstand() > 350 || AnimCount > 20.0f) {
                Handlung = GEGNER::LAUFEN;
                AnimPhase = 0;
                AnimStart = 0;
                AnimEnde = 10;
                shotdelay = static_cast<float>(GetRandom(20) + 20);
            }
        } break;

        // rumfliegen, weil abgeschossen ?
        //
        case GEGNER::FALLEN: {
            rot += Timer.sync(static_cast<float>(Value2));

            clampAngle(rot);

            // An Wand gestossen ?
            //
            if (blocko & BLOCKWERT_WAND || blocku & BLOCKWERT_WAND || blockl & BLOCKWERT_WAND ||
                blockr & BLOCKWERT_WAND)
                Energy = 0.0f;

            shotdelay -= Timer.sync(1.0f);

            if (shotdelay < 0.0f) {
                shotdelay = Timer.sync(8.0f);
                PartikelSystem.PushPartikel(xPos + 35.0f + static_cast<float>(GetRandom(5)),
                                            yPos + 20.0f + static_cast<float>(GetRandom(5)), ROCKETSMOKE);
                PartikelSystem.PushPartikel(xPos + 30.0f + static_cast<float>(GetRandom(5)),
                                            yPos + 20.0f + static_cast<float>(GetRandom(5)), SMOKE3);
                PartikelSystem.PushPartikel(xPos + 30.0f + static_cast<float>(GetRandom(5)),
                                            yPos + 20.0f + static_cast<float>(GetRandom(5)), FUNKE);
            }
        } break;
    }

    // Spieler berührt ?
    //
    if (Handlung != GEGNER::FALLEN)
        TestDamagePlayers(Timer.sync(4.0f));

    // Spinne abgeknallt ?
    // Dann Explosion erzeugen und Spinne lossegeln lassen ;)
    //
    if (Energy <= 0.0f && Handlung != GEGNER::FALLEN) {
        Energy = 100.0f;
        Handlung = GEGNER::FALLEN;
        xSpeed = static_cast<float>(GetRandom(15)) - 7.0f, ySpeed = -static_cast<float>(GetRandom(8)) - 8.0f;
        yAcc = 3.0f;

        // Drehspeed beim Runterfallen setzen
        //
        Value2 = GetRandom(20) + 20;

        // evtl negativ (andere Richtung drehen)
        //
        if (GetRandom(2) == 0)
            Value2 *= -1;

        SoundManager.PlayWave(100, 128, 8000 + GetRandom(4000), SOUND::EXPLOSION1);
        PartikelSystem.PushPartikel(xPos + 5, yPos, EXPLOSION_MEDIUM2);

        shotdelay = 1.0f;
    }
}

// --------------------------------------------------------------------------------------
// FireSpider explodiert
// --------------------------------------------------------------------------------------

void GegnerFireSpider::GegnerExplode() {
    SoundManager.PlayWave(100, 128, 8000 + GetRandom(4000), SOUND::EXPLOSION1);
    PartikelSystem.PushPartikel(xPos + 5, yPos, EXPLOSION_MEDIUM2);

    for (int i = 0; i < 10; i++) {
        PartikelSystem.PushPartikel(xPos + static_cast<float>(GetRandom(40)),
                                    yPos + static_cast<float>(GetRandom(30)), SPIDERSPLITTER);
        PartikelSystem.PushPartikel(xPos + static_cast<float>(GetRandom(40)),
                                    yPos + static_cast<float>(GetRandom(30)), FUNKE);
    }

    Player[0].Score += 250;
}
