// map.cpp: declarations for map functions
#include <iostream>
#include "map.h"

map::map(int X,int Y,int NgY,int NgX) {
	MapMaxSizeX=X;
	MapMaxSizeY=Y;
	MapMaxSizeNgY=NgY;
	MapMaxSizeNgX=NgX;
	currentSquareX=0,currentSquareY=0;
	groundID=0;

	for (int i=0;i<max;i++) {
		itemSquareX[i]=0;
		itemSquareY[i]=0;
		itemSquareNgX[i]=0;
		itemSquareNgY[i]=0;
		itemLineX[i]=NULL;
		itemLineNgX[i]=NULL;
		itemLineY[i]=NULL;
		itemLineNgY[i]=NULL;
	}
};

map::~map() {};

void map::addItemX(item *thisItem,int spawnX) {
	if (spawnX<0) {
		itemSquareNgX[spawnX-1]=spawnX;
		itemLineNgX[spawnX-1]=thisItem;
	}
	if (spawnX>0) {
		itemSquareX[spawnX-1]=spawnX;
		itemLineX[spawnX-1]=thisItem;
	}
};

void map::addItemY(item *thisItem,int spawnY) {
	if (spawnY<0) {
		itemSquareNgY[spawnY-1]=spawnY;
		itemLineNgY[spawnY-1]=thisItem;
	}
	if (spawnY>0) {
		itemSquareY[spawnY-1]=spawnY;
		itemLineY[spawnY-1]=thisItem;
	}
};

void map::removeItemX(int spawnX) {
	if (spawnX<0) {
		itemSquareNgX[spawnX-1]=0;
		itemLineNgX[spawnX-1]=0;
	}
	if (spawnX>0) {
		itemSquareX[spawnX-1]=0;
		itemLineX[spawnX-1]=0;
	}
};

void map::removeItemY(int spawnY) {
	if (spawnY<0) {
		itemSquareNgY[spawnY-1]=0;
		itemLineNgY[spawnY-1]=0;
	}
	if (spawnY>0) {
		itemSquareY[spawnY-1]=0;
		itemLineY[spawnY-1]=0;
	}
};

bool map::itemExists(map *karte,int currentX,int currentY) {
	currentX=karte->getCurrentSpaceX();
	currentY=karte->getCurrentSpaceY();
	if (currentX==0 && currentY==0)
		return false;

	if (currentX==0 || currentY==0)
		return false;
	
	if (currentX<0 && currentY<0) { // if both X & Y are <0
		if (itemSquareNgX[currentX-1]==currentX && itemSquareNgY[currentY-1]==currentY)
			return true;
		else
			return false;
	}
	if (currentX>0 && currentY>0) { // if both X & Y are >0
	        if (itemSquareX[currentX-1]==currentX && itemSquareY[currentY-1]==currentY)
		        return true;
		else
		 	return false;
	}
	if (currentX<0 && currentY>0) { // if X<0 BUT Y>0
	        if (itemSquareNgX[currentX-1]==currentX && itemSquareY[currentY-1]==currentY)
	                return true;
	        else
	                return false;
	}
	if (currentX>0 && currentY<0) { // if X>0 BUT Y<0
                if (itemSquareX[currentX-1]==currentX && itemSquareNgY[currentY-1]==currentY)
	                return true;
	        else
	                return false;
	}
};

std::string map::identifyItem(map *karte) {
	int currentX=karte->getCurrentSpaceX();
	int currentY=karte->getCurrentSpaceY();
	
	if (currentX>currentY) {
		if (currentX<0)
			return itemLineNgX[currentX-1]->getName();
		if (currentX>0)
			return itemLineX[currentX-1]->getName();
	}

	if (currentX<currentY) {
		if (currentY<0)
			return itemLineNgY[currentY-1]->getName();
		if (currentY>0)
			return itemLineY[currentY-1]->getName();
	}

	if (currentX==currentY) {
		std::string xName,yName;
		if (currentX>0 && currentY>0) {
			xName=itemLineX[currentX-1]->getName();
			yName=itemLineY[currentY-1]->getName();
			if (xName==yName)
				return xName;
			if (xName!=yName)
				return "nothing";
		}
		if (currentX<0 && currentY<0) {
			xName=itemLineNgX[currentX-1]->getName();
			yName=itemLineNgY[currentY-1]->getName();
			if (xName==yName)
				return xName;
			if (xName!=yName)
				return "nothing";
		}
	}
			
	else
		return "nothing";
};

TYPE map::checkItemType(map *karte) {
	int currentX=karte->getCurrentSpaceX();
	int currentY=karte->getCurrentSpaceY();

	if (currentX>currentY) {
		if (currentX<0)
			return itemLineNgX[currentX-1]->checkType();
		if (currentX>0)
			return itemLineX[currentX-1]->checkType();
	}

	if (currentX<currentY) {
		if (currentY<0)
			return itemLineNgY[currentY-1]->checkType();
		if (currentY>0)
			return itemLineY[currentY-1]->checkType();
	}

	if (currentX==currentY) {
		TYPE xType,yType;
		if (currentX>0 && currentY>0) {
			xType=itemLineX[currentX-1]->checkType();
			yType=itemLineY[currentY-1]->checkType();
			if (xType==yType)
				return xType;
			if (xType!=yType)
				return npe;
		}
		if (currentX<0 && currentY<0) {
			xType=itemLineNgX[currentX-1]->checkType();
			yType=itemLineNgY[currentY-1]->checkType();
			if (xType==yType)
				return xType;
			if (xType!=yType)
				return npe;
		}
	}
			
	else
		return npe;
};

