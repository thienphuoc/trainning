#pragma once
#include "cocos2d.h"
#include <vector>
#include <array>
#include "Definations.h"

class AI 
{
public:
    AI(m_Node playerPiece);

    void PlacePiece(m_Node(*gridArray)[9], cocos2d::Scene* scene);

private:
    void CheckSection(int Point1, int Point2, int Point3, m_Node pieceToCheck, m_Node(*gridArray)[9], cocos2d::Scene* scene);
    void CheckIfPieceIsEmpty(int Point, m_Node(*gridArray)[9], cocos2d::Scene* scene);
    void drawNode(cocos2d::Scene* scene, int point);
    m_Node aiPiece;
    m_Node playerPiece;

    std::vector<std::array<int, 3>> checkMatchVector;

};