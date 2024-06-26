// --------------------------------------------------------------------------------------
// Der Piranha
//
// Schwimmt von einer Beckenseite zur anderen und flitzt auf den Spieler zu, wenn
// er in der Nähe ist
// --------------------------------------------------------------------------------------

#include "Gegner_Piranha.hpp"
#include "stdafx.hpp"

// --------------------------------------------------------------------------------------
// Piranha Konstruktor

GegnerPiranha::GegnerPiranha(int Wert1, int Wert2, bool Light) {
    Handlung = GEGNER::LAUFEN;
    HitSound = 1;
    AnimStart = 0;
    AnimEnde = 10;
    AnimSpeed = 0.75f;
    if (GetRandom(2) == 0)
        BlickRichtung = DirectionEnum::LINKS;
    else
        BlickRichtung = DirectionEnum::RECHTS;
    xSpeed = -8.0;
    ySpeed = 0.0f;
    xAcc = 0.0f;
    yAcc = 0.0f;
    Energy = 30;
    Value1 = Wert1;
    Value2 = Wert2;

    // vom bigfish ausgespuckt
    if (Value1 == 98) {
        Value1 = 99;
        Value2 = 0;
        Handlung = GEGNER::SPECIAL;

        xSpeed = -20.0f - GetRandom(20);
        xsave = xSpeed;
        ySpeed = static_cast<float>(Wert2) * 3;
        ysave = ySpeed;

        AnimCount = 1.0f;
    } else

        if (Value2 != 1)
        Value2 = GetRandom(20) + 2;
    ChangeLight = Light;
    Destroyable = true;
    OwnDraw = true;
}

// --------------------------------------------------------------------------------------
// Eigene Draw Funktion
// --------------------------------------------------------------------------------------

void GegnerPiranha::DoDraw() {
    // Piranha rendern
    //
    bool mirror = (BlickRichtung != DirectionEnum::LINKS);

    // Spieler angreifen?
    int off;
    if (Value1 == 99)
        off = 0;

    // oder nur rumschwimmen
    else
        off = 20;

    pGegnerGrafix[GegnerArt]->RenderSprite(xPos - TileEngine.XOffset,
                                           yPos - TileEngine.YOffset, off + AnimPhase, 0xFFFFFFFF,
                                           mirror);
}

// --------------------------------------------------------------------------------------
// Piranha Bewegungs KI

void GegnerPiranha::DoKI() {
    if (Handlung != GEGNER::SPECIAL)
        SimpleAnimation();

    // Nach links bzw rechts auf Kollision prüfen und dann ggf umkehren
    //
    if ((xSpeed < 0.0f && (blockl & BLOCKWERT_WAND || blockl & BLOCKWERT_GEGNERWAND)) ||
        (xSpeed > 0.0f && (blockr & BLOCKWERT_WAND || blockr & BLOCKWERT_GEGNERWAND)))

    {
        xSpeed = 0;
        Handlung = GEGNER::DREHEN;
        AnimPhase = 10;
        AnimStart = 0;
        AnimEnde = 15;
    }

    // Spieler im Wasser und in Sichtweite ? Dann verfolgen
    if (pAim->InLiquid == true && Value1 == 99 && (PlayerAbstand() <= 150 || Value2 == 1)) {
        if (pAim->ypos + 4 + Value2 < yPos &&  // Spieler oberhalb oder
            !(blocko & BLOCKWERT_WAND) && !(blocko & BLOCKWERT_GEGNERWAND) && blocko & BLOCKWERT_WASSER)
            yPos -= Timer.sync(4.0f);

        if (pAim->ypos + 4 + Value2 > yPos &&  // unterhalb des Piranhas
            !(TileEngine.BlockUnten(xPos, yPos, xPosOld, yPosOld, GegnerRect[GegnerArt]) & BLOCKWERT_WAND) &&
            !(TileEngine.BlockUnten(xPos, yPos, xPosOld, yPosOld, GegnerRect[GegnerArt]) & BLOCKWERT_GEGNERWAND))
            yPos += Timer.sync(4.0f);  // Dann auf ihn zu schwimmen
    }

    // Je nach Handlung richtig verhalten
    //
    switch (Handlung) {
        case GEGNER::SPECIAL: {
            AnimCount -= Timer.sync(0.1f);

            xSpeed = xsave * AnimCount;
            ySpeed = ysave * AnimCount;

            if (AnimCount < 0.0f) {
                xSpeed = 0.0;
                ySpeed = 0.0f;
                Value2 = 1;
                Value1 = 99;
                Handlung = GEGNER::LAUFEN;
            }

        } break;

        case GEGNER::LAUFEN:  // Piranha schwimmt rum
        {
            if (pAim->InLiquid == true &&                                 // Spieler im Wasser und
                Value1 == 99 && (PlayerAbstand() <= 150 || Value2 == 1))  // in Sichtweite ?
            {
                if (BlickRichtung == DirectionEnum::LINKS)  // Dann schneller schwimmen
                    xSpeed = -14.0f;
                else
                    xSpeed = 14.0f;

                // Piranha links oder rechts am Spieler vorbei ?
                // Dann umdrehen und weiter verfolgen
                if (Handlung == GEGNER::LAUFEN) {
                    if ((BlickRichtung == DirectionEnum::LINKS && pAim->xpos > xPos + GegnerRect[GegnerArt].right - 20) ||

                        (BlickRichtung == DirectionEnum::RECHTS && pAim->xpos + pAim->CollideRect.right < xPos)) {
                        xSpeed = 0;
                        Handlung = GEGNER::DREHEN;
                        AnimPhase = 10;
                        AnimStart = 0;
                        AnimEnde = 15;
                    }
                }
            } else {
                if (BlickRichtung == DirectionEnum::LINKS)
                    xSpeed = -static_cast<float>(GetRandom(10) + 4);
                else
                    xSpeed = static_cast<float>(GetRandom(10) + 4);
            }
        } break;

        case GEGNER::DREHEN:  // Piranha dreht sich um
        {
            if (AnimPhase == AnimStart) {
                Handlung = GEGNER::LAUFEN;
                AnimEnde = 10;
                AnimStart = 0;
                AnimPhase = 0;

                if (BlickRichtung == DirectionEnum::LINKS)  // Ab jetzt in die andere Richtung schwimmen
                {
                    BlickRichtung = DirectionEnum::RECHTS;
                    xSpeed = 8.0f;
                } else {
                    BlickRichtung = DirectionEnum::LINKS;
                    xSpeed = -8.0f;
                }
            }
        } break;

        default:
            break;
    }  // switch

    // Testen, ob der Spieler den Piranha berührt hat
    TestDamagePlayers(Timer.sync(1.0f));
}

// --------------------------------------------------------------------------------------
// Piranha explodiert

void GegnerPiranha::GegnerExplode() {
    // Fetzen und Blasen erzeugen

    for (int i = 0; i < 3; i++)
        PartikelSystem.PushPartikel(xPos - 20.0f + static_cast<float>(GetRandom(45)),
                                    yPos - 5.0f + static_cast<float>(GetRandom(30)), PIRANHATEILE);

    for (int i = 0; i < 3; i++)
        PartikelSystem.PushPartikel(xPos - 10.0f + static_cast<float>(GetRandom(45)),
                                    yPos + 10.0f + static_cast<float>(GetRandom(30)), BUBBLE);

    // Blutwolke dazu
    PartikelSystem.PushPartikel(xPos + 2.0f,
                                yPos - 5.0f, PIRANHABLUT);

    SoundManager.PlayWave(100, 128, -GetRandom(2000) + 11025, SOUND::EXPLOSION1);  // Sound ausgeben

    Player[0].Score += 200;
}
