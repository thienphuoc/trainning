#include "AI.h"
#include <iostream>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "2d/CCNode.h"
using namespace std;
USING_NS_CC;
AI::AI(m_Node playerPiece)
{
	this->playerPiece = playerPiece;

	if (O_PIECE == playerPiece)
	{
		aiPiece = X_PIECE;
	}
	else
	{
		aiPiece = O_PIECE;
	}

	checkMatchVector.push_back({ 2, 5, 8 });
	checkMatchVector.push_back({ 2, 1, 0 });
	checkMatchVector.push_back({ 2, 4, 6 });
	checkMatchVector.push_back({ 8, 5, 2 });
	checkMatchVector.push_back({ 8, 7, 6 });
	checkMatchVector.push_back({ 8, 5, 0 });
	checkMatchVector.push_back({ 0, 1, 2 });
	checkMatchVector.push_back({ 0, 3, 6 });
	checkMatchVector.push_back({ 0, 4, 8 });
	checkMatchVector.push_back({ 6, 7, 8 });
	checkMatchVector.push_back({ 6, 3, 0 });
	checkMatchVector.push_back({ 6, 4, 2 });
	checkMatchVector.push_back({ 1, 4, 7 });
	checkMatchVector.push_back({ 5, 4, 3 });
	checkMatchVector.push_back({ 7, 4, 1 });
	checkMatchVector.push_back({ 3, 4, 5 });
	checkMatchVector.push_back({ 1, 7, 4 });
	checkMatchVector.push_back({ 5, 3, 4 });
	checkMatchVector.push_back({ 2, 6, 4 });
	checkMatchVector.push_back({ 8, 0, 4 });
	checkMatchVector.push_back({ 2, 8, 5 });
	checkMatchVector.push_back({ 0, 6, 3 });
	checkMatchVector.push_back({ 2, 0, 1 });
	checkMatchVector.push_back({ 8, 6, 7 });
}

void AI::PlacePiece(m_Node(*gridArray)[9], cocos2d::Scene* scene)
{
	try
	{
		// check if AI can win
		for (int i = 0; i < checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], AI_PIECE, gridArray, scene);
		}

		// check if player can win
		for (int i = 0; i < checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], PLAYER_PIECE, gridArray, scene);
		}

		// check if center is empty
		CheckIfPieceIsEmpty(4, gridArray, scene);

		// check if a corner is empty
		CheckIfPieceIsEmpty(2, gridArray, scene);
		CheckIfPieceIsEmpty(8, gridArray, scene);
		CheckIfPieceIsEmpty(0, gridArray, scene);
		CheckIfPieceIsEmpty(6, gridArray, scene);

		// check for any other empty piece
		CheckIfPieceIsEmpty(1, gridArray, scene);
		CheckIfPieceIsEmpty(3, gridArray, scene);
		CheckIfPieceIsEmpty(5, gridArray, scene);
		CheckIfPieceIsEmpty(7, gridArray, scene);
	}
	catch (int error)
	{
	}
}

void AI::CheckSection(int Point1, int Point2, int Point3, m_Node pieceToCheck, m_Node(*gridArray)[9], cocos2d::Scene* scene)
{
	// check if 2 pieces match
	if ((*gridArray)[Point1] == pieceToCheck && (*gridArray)[Point2] == pieceToCheck)
	{
		if (EMPTY_PIECE == (*gridArray)[Point3])
		{
			(*gridArray)[Point3] = AI_PIECE;
			drawNode(scene, Point3);
			throw - 1;
		}
	}
}

void AI::CheckIfPieceIsEmpty(int Point, m_Node(*gridArray)[9], cocos2d::Scene* scene)
{
	// check if
	if (EMPTY_PIECE == (*gridArray)[Point])
	{
		(*gridArray)[Point] = AI_PIECE;
		drawNode(scene, Point);

		throw - 2;
	}
}

void AI::drawNode(cocos2d::Scene* scene, int point)
{
	__String* buttonName = __String::createWithFormat("map_button_%i", point+1);
	__String* imageName = __String::createWithFormat("map_image_%i", point+1);
	auto nodeButton = utils::findChild<ui::Button*>(scene, buttonName->getCString());
	auto imageButton = utils::findChild<ui::ImageView*>(scene, imageName->getCString());
	imageButton->loadTexture(O_IMAGE_PATH);
	imageButton->setScale(0.35);
	nodeButton->setBright(false);
	nodeButton->setTouchEnabled(false);
}