// localization.h
#ifndef LOCALIZATION_H
#define LOCALIZATION_H

void localizationInit();
int getRow();
int getCol();
int getHeading();

float expectedWallDistance();
void updatePositionAfterMove(int cells);
void updateHeadingAfterTurn(bool clockwise);

bool localize();  // returns true if correction was applied

#endif