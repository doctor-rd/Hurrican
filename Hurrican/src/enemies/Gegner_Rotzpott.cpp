// --------------------------------------------------------------------------------------
// Der hingerotzte Ballerpott
//
// Schiesst genau auf den Spieler
// Ist der Spieler unterhalb des Potts, schiesst er im Bogen
// ansonsten schiesst er Laser wie die Zitrone
// --------------------------------------------------------------------------------------

#include "Gegner_Rotzpott.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerRotzpott::GegnerRotzpott(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::STEHEN;
    Energy = 70;
    ChangeLight = Light;
    Destroyable = true;
    GunWinkel = 0.0f;
    NewWinkel = 0.0f;
    OwnDraw = true;
    TestBlock = false;
    ShotDelay = 5.0f;
}

// --------------------------------------------------------------------------------------
// Knarre zeigt auf Hurrican
// --------------------------------------------------------------------------------------

void GegnerRotzpott::CalcKnarreWinkel() {
    // Gegner auf Spieler ausrichten
    //
    static float dir = 0.0f;

    clampAngle(GunWinkel);

    float dx, dy;
    if (pAim->ypos > yPos + 30) {
        dx = (xPos + 27) - (pAim->xpos + 35);
        dy = (yPos + 20) - (pAim->ypos + 40);

        if (dx > 0.0f)
            NewWinkel = dx * 0.12f + dy * 0.033f;
        else
            NewWinkel = dx * 0.12f - dy * 0.033f;
    } else {
        // Abstände berechnen
        dx = (xPos + 27) - (pAim->xpos + 35);
        dy = (yPos + 20) - (pAim->ypos + 40);

        // Division durch Null verhinden
        if (dy == 0.0f)
            dy = 0.01f;

        float w;

        // DKS - converted to float, used rad/cos macros:
        // w = static_cast<float>(atan(dx / dy) * 360.0f / (D3DX_PI * 2));
        w = RadToDeg(atanf(dx / dy));

        if (dx >= 0.0f && dy >= 0.0f)
            NewWinkel = w;
        else if (dx > 0.0f && dy < 0.0f)
            NewWinkel = 180.0f + w;
        else if (dx < 0.0f && dy > 0.0f)
            NewWinkel = 360.0f + w;
        else if (dx < 0.0f && dy < 0.0f)
            NewWinkel = 180.0f + w;
    }

    clampAngle(NewWinkel);

    // neue Drehrichtung festlegen
    if (NewWinkel > GunWinkel) {
        if (NewWinkel - GunWinkel > 180.0f)
            dir = -30.0f;
        else
            dir = 30.0f;
    }

    if (NewWinkel < GunWinkel) {
        if (GunWinkel - NewWinkel < 180.0f)
            dir = -30.0f;
        else
            dir = 30.0f;
    }

    // Knarre an neuen Winkel annähern
    if (dir < 0.0f) {
        GunWinkel += Timer.sync(dir);

        if (GunWinkel < NewWinkel)
            GunWinkel = NewWinkel;
    } else if (dir > 0.0f) {
        GunWinkel += Timer.sync(dir);

        if (GunWinkel > NewWinkel)
            GunWinkel = NewWinkel;
    }
}

// --------------------------------------------------------------------------------------
// Draw
// --------------------------------------------------------------------------------------

void GegnerRotzpott::DoDraw() {
    // Knarre
    Gegner.DroneGun.RenderSpriteRotatedOffset(-TileEngine.XOffset + xPos + 20.0f,
                                              -TileEngine.YOffset + yPos - 28.0f,
                                              GunWinkel, 0, 0, 0xFFFFFFFF);

    // Körper
    pGegnerGrafix[GegnerArt]->RenderSprite(-TileEngine.XOffset + xPos,
                                           -TileEngine.YOffset + yPos, 0, 0xFFFFFFFF);

    AlreadyDrawn = true;
}

// --------------------------------------------------------------------------------------
// "Bewegungs KI"
// --------------------------------------------------------------------------------------

void GegnerRotzpott::DoKI() {
    // Knarre ausrichten

    // Testen, ob der Spieler den gegner berührt hat
    //
    TestDamagePlayers(Timer.sync(2.0f));

    CalcKnarreWinkel();

    // schiessen, wenn Spieler in der Nähe und Turm kurz
    // vor finalem Winkel?
    if (PlayerAbstand() < 400 && abs(static_cast<int>(GunWinkel - NewWinkel)) < 10)
        ShotDelay -= Timer.sync(1.0f);

    if (ShotDelay <= 0.0f) {
        // DKS - Support new trig sin/cos lookup table and use deg/rad versions of sin/cos:
        // PartikelSystem.PushPartikel(xPos - (float)sin((180 - GunWinkel) / 180.0f * PI) * 30.0f,
        //                              yPos - 18.0f + (float)cos((180 - GunWinkel) / 180.0f * PI) * 38.0f,
        //                              LASERFLAMEPHARAO);
        PartikelSystem.PushPartikel(xPos - sin_deg(180.0f - GunWinkel) * 30.0f,
                                    yPos - 18.0f + cos_deg(180.0f - GunWinkel) * 38.0f, LASERFLAMEPHARAO);

        // Wie schiesst er? Im Bogen oder direkt?
        if (pAim->ypos > yPos + 30) {
            ShotDelay = 9.0f;
            SoundManager.PlayWave(100, 128, 16000 + GetRandom(500), SOUND::LASERSHOT);
            WinkelUebergabe = 360.0f - GunWinkel + (static_cast<float>(GetRandom(10) - 5)) / 2.0f;
            // DKS - Support new trig sin/cos lookup table and use deg/rad versions of sin/cos:
            // Projectiles.PushProjectile(xPos + 20.0f - (float)sin((180 - GunWinkel) / 180.0f * PI) * 25.0f,
            //                             yPos - 12.0f + (float)cos((180 - GunWinkel) / 180.0f * PI) * 20.0f,
            //                             ROTZSHOT);
            Projectiles.PushProjectile(xPos + 20.0f - sin_deg(180.0f - GunWinkel) * 25.0f,
                                       yPos - 12.0f + cos_deg(180.0f - GunWinkel) * 20.0f, ROTZSHOT);
        } else {
            ShotDelay = 7.0f;
            SoundManager.PlayWave(100, 128, 24000 + GetRandom(500), SOUND::LASERSHOT);
            WinkelUebergabe = 360.0f - GunWinkel;
            // DKS - Support new trig sin/cos lookup table and use deg/rad versions of sin/cos:
            // Projectiles.PushProjectile(xPos + 24.0f - (float)sin((180 - GunWinkel) / 180.0f * PI) * 45.0f,
            //                             yPos - 12.0f + (float)cos((180 - GunWinkel) / 180.0f * PI) * 45.0f,
            //                             FLUGLASER);
            Projectiles.PushProjectile(xPos + 24.0f - sin_deg(180.0f - GunWinkel) * 45.0f,
                                       yPos - 12.0f + cos_deg(180.0f - GunWinkel) * 45.0f, FLUGLASER);
        }
    }
}

// --------------------------------------------------------------------------------------
// GegnerRotzpott explodiert
// --------------------------------------------------------------------------------------

void GegnerRotzpott::GegnerExplode() {
    SoundManager.PlayWave(100, 128, 8000 + GetRandom(4000), SOUND::EXPLOSION1);

    for (int i = 0; i < 8; i++) {
        PartikelSystem.PushPartikel(xPos - 10.0f + static_cast<float>(GetRandom(40)),
                                    yPos - 10.0f + static_cast<float>(GetRandom(20)), EXPLOSION_MEDIUM2);
        PartikelSystem.PushPartikel(xPos - 10.0f + static_cast<float>(GetRandom(40)),
                                    yPos - 10.0f + static_cast<float>(GetRandom(20)), SPIDERSPLITTER);
    }

    for (int i = 0; i < 4; i++)
        PartikelSystem.PushPartikel(xPos - 10.0f + static_cast<float>(GetRandom(40)),
                                    yPos - 10.0f + static_cast<float>(GetRandom(20)), SCHROTT1);

    Player[0].Score += 350;
}
