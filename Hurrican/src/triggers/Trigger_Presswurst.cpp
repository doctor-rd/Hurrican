// --------------------------------------------------------------------------------------
// Die Presswurst
//
// Kommt runter, zermatscht den Hurrican und pflanzt Spinnen
// und wartet dann solange wie es Value2 angibt
// --------------------------------------------------------------------------------------

#include "Trigger_Presswurst.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Konstruktor
// --------------------------------------------------------------------------------------

GegnerPresswurst::GegnerPresswurst(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::INIT;
    BlickRichtung = DirectionEnum::LINKS;
    Energy = 100;
    Value1 = Wert1;
    Value2 = Wert2;
    AnimPhase = 0;
    ChangeLight = Light;
    Destroyable = false;
    Active = true;
    OwnDraw = true;
    TestBlock = false;
    oldy = 0.0f;
    SmokeCount = 0.0f;
}

// --------------------------------------------------------------------------------------
// Rendern
// --------------------------------------------------------------------------------------

void GegnerPresswurst::DoDraw() {
    // rendern
    //
    int size = static_cast<int>(oldy - yPos) + GegnerRect[GegnerArt].top;
    pGegnerGrafix[GegnerArt]->SetRect(0, size, 185, 357);
    pGegnerGrafix[GegnerArt]->RenderSprite(xPos - TileEngine.XOffset,
                                           yPos - TileEngine.YOffset + static_cast<float>(size), 0xFFFFFFFF);
}

// --------------------------------------------------------------------------------------
// Bewegungs KI
// --------------------------------------------------------------------------------------

void GegnerPresswurst::DoKI() {
    // Spieler kann von unten nicht durchspringen
    //
    for (int p = 0; p < NUMPLAYERS; p++)
        if (SpriteCollision(Player[p].xpos, Player[p].ypos, Player[p].CollideRect, xPos, yPos, GegnerRect[GegnerArt]) ==
                true &&
            yPos < Player[p].ypos && Player[p].yspeed < 0.0f)
            Player[p].yspeed *= -0.25f;

    // Kollisionsrechteck fürs Wegschieben
    GegnerRect[GegnerArt].top = 0;
    Wegschieben(GegnerRect[GegnerArt], 0.0f);

    // Kollisionsrechteck für das Unterteil
    GegnerRect[GegnerArt].top = 251;

    blocko = TileEngine.BlockOben(xPos, yPos, yPosOld, yPosOld, GegnerRect[GegnerArt]);
    blocku = TileEngine.BlockUntenNormal(xPos, yPos, yPosOld, yPosOld, GegnerRect[GegnerArt]);

    // Ja nach Handlung richtig verhalten
    switch (Handlung) {
        // Am Anfang einmal initialisieren
        case GEGNER::INIT: {
            yPos -= GegnerRect[GegnerArt].top;
            oldy = yPos;
            Handlung = GEGNER::INIT2;

        } break;

        // Auf Spieler warten
        case GEGNER::INIT2: {
            for (int p = 0; p < NUMPLAYERS; p++)
                if (Player[p].ypos > yPos && PlayerAbstandHoriz(&Player[p]) < 200 &&
                    PlayerAbstandVert(&Player[p]) < 500) {
                    Handlung = GEGNER::LAUFEN;
                    ySpeed = 10.0f;
                    yAcc = 2.5f;

                    if (PlayerAbstand(true) < 600)
                        SoundManager.PlayWave3D(static_cast<int>(xPos + 90.0f),
                                                static_cast<int>(yPos + 330.0f), 11025,
                                                SOUND::PRESSE);
                }
        } break;

        // Pressen
        case GEGNER::LAUFEN: {
            // Spieler beim Runterfallen berührt? Dann stirbt er leider ;)
            //
            for (int p = 0; p < NUMPLAYERS; p++)
                if (SpriteCollision(Player[p].xpos, Player[p].ypos, Player[p].CollideRect, xPos, yPos,
                                    GegnerRect[GegnerArt]) == true &&
                    Player[p].ypos > yPos) {
                    // wenn er steht, dann gleich zerquetschen
                    if (Player[p].Handlung != PlayerActionEnum::SPRINGEN)
                        Player[p].DamagePlayer(500.0f);

                    // wenn er springt, dann runterdrücken
                    else {
                        // pPlayer->yspeed = 0.0f;
                        // pPlayer->yadd = 0.0f;
                        Player[p].ypos = yPos + GegnerRect[PRESSWURST].bottom;
                    }
                }

            // Am Boden ? Dann Partikel erzeugen und zum "Produzieren" wechseln
            if (ySpeed > 0.0f && (blocku & BLOCKWERT_WAND || blocku & BLOCKWERT_GEGNERWAND)) {
                // Spieler beim Runterfallen berührt? Dann stirbt er leider ;)
                //
                for (int p = 0; p < NUMPLAYERS; p++)
                    if (SpriteCollision(Player[p].xpos, Player[p].ypos, Player[p].CollideRect, xPos, yPos,
                                        GegnerRect[GegnerArt]) == true &&
                        Player[p].ypos > yPos)
                        Player[p].DamagePlayer(500.0f);

                // DKS - Disabled this, as it had no effect (default paremeter resolv==false and
                //      return value isn't used here for anything:
                // TileEngine.BlockUnten(xPos, yPos, yPosOld, yPosOld, GegnerRect[GegnerArt]);

                ySpeed = 0.0f;
                yAcc = 0.0f;
                SmokeCount = 5.0f;

                if (PlayerAbstand() < 600)
                    SoundManager.PlayWave3D(static_cast<int>(xPos + 90.0f),
                                            static_cast<int>(yPos + 330.0f), 11025,
                                            SOUND::DOORSTOP);

                ShakeScreen(2.0f);

                Handlung = GEGNER::SPECIAL;
            }

            // An der Decke ? Dann wieder in den Wartezustand setzen
            if (ySpeed < 0.0f && (blocko & BLOCKWERT_WAND || blocko & BLOCKWERT_GEGNERWAND)) {
                ySpeed = 0.0f;
                yAcc = 0.0f;

                Handlung = GEGNER::INIT2;
            }

        } break;

        // Presse wartet unten und spuckt dann Dampf
        case GEGNER::SPECIAL: {
            SmokeCount -= Timer.sync(1.0f);

            if (SmokeCount <= 0.0f) {
                Handlung = GEGNER::SPECIAL2;
                AnimCount = 28.0f;
                if (PlayerAbstand() < 600)
                    SoundManager.PlayWave3D(static_cast<int>(xPos + 90.0f),
                                            static_cast<int>(yPos + 330.0f), 13000,
                                            SOUND::STEAM2);
            }
        } break;

        // Presse dampft
        case GEGNER::SPECIAL2: {
            // rauchen lassen
            SmokeCount -= Timer.sync(1.0f);
            if (SmokeCount <= 0.0f) {
                SmokeCount = 0.2f;

                PartikelSystem.PushPartikel(xPos + 30.0f, yPos + 300.0f, SMOKE3_LU);
                PartikelSystem.PushPartikel(xPos + 135.0f, yPos + 300.0f, SMOKE3_RU);
            }

            // Spinne spawnen
            AnimCount -= Timer.sync(1.0f);
            if (AnimCount < 0.0f) {
                // Spinne spawnen
                Gegner.PushGegner(xPos + 60.0f,
                                  yPos + 357.0f - GegnerRect[SPIDERBOMB].bottom,
                                  SPIDERBOMB, 0, 0, false, true);

                // wieder hochfahren
                Handlung = GEGNER::LAUFEN;
                ySpeed = -15.0f;
                yAcc = 0.2f;

                if (PlayerAbstand() < 600)
                    SoundManager.PlayWave3D(static_cast<int>(xPos + 90.0f),
                                            static_cast<int>(yPos + 330.0f), 11025,
                                            SOUND::PRESSE);
            }
        } break;

    }  // switch
}

// --------------------------------------------------------------------------------------
// Presswurst explodiert (geht ja garnich *g*)
// --------------------------------------------------------------------------------------

void GegnerPresswurst::GegnerExplode() {}
