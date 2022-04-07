
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void House::Draw() const
{
	MyTools::SetColor(CC_Yellow);
	/*
	GotoXY(x, y - 5);
	cout << "  ########  ";
	GotoXY(x, y - 4);
	cout << "##        ##";
	GotoXY(x, y - 3);
	cout << "############";
	GotoXY(x, y - 2);
	cout << "#          #";
	GotoXY(x, y - 1);
	cout << "#          #";
	GotoXY(x, y);
	cout << "############";
	*/
	
	for (size_t i = 0; i < 7; i++)
	{
		GotoXY(x, y - i);
		for (size_t j = 0; j < 14; j++)
		{
			cout << look[i][j];
		}
		cout << endl;
	}
}

void HouseBuilderA::buildch()
{
	for (size_t i = 0; i < 7; i++)
	{
		for (size_t j = 0; j < 14; j++)
		{
			h->look[i][j] = ' ';
		}
	}
};

void HouseBuilderA::buildroof()
{
	for (size_t i = 0; i < 14; i++)
	{
		h->look[0][i] = '#';
	}
};
void HouseBuilderA::buildwallR() 
{
	for (size_t i = 0; i < 7; i++)
	{
		h->look[i][13] = '#';
	}
};
void HouseBuilderA::buildwallL()
{
	for (size_t i = 0; i < 7; i++)
	{
		h->look[i][0] = '#';
	}
};
void HouseBuilderA::buildfloor()
{
	for (size_t i = 0; i < 14; i++)
	{
		h->look[6][i] = '#';
	}
};

void HouseBuilderB::buildch()
{
	for (size_t i = 0; i < 7; i++)
	{
		for (size_t j = 0; j < 14; j++)
		{
			h->look[i][j] = ' ';
		}
	}
};
void HouseBuilderB::buildroof()
{
	for (size_t i = 0; i < 14; i++)
	{
		h->look[5][i] = '#';
	}
};
void HouseBuilderB::buildwallR()
{
	for (size_t i = 0; i < 5; i++)
	{
		h->look[i][13] = '#';
	}
};
void HouseBuilderB::buildwallL()
{
	for (size_t i = 0; i < 5; i++)
	{
		h->look[i][0] = '#';
	}
};
void HouseBuilderB::buildfloor()
{
	for (size_t i = 0; i < 14; i++)
	{
		h->look[0][i] = '#';
	}
};
void HouseBuilderB::buildwindow()
{
	h->look[2][7] = '#';
	h->look[2][8] = '#';
	h->look[2][9] = '#';
	h->look[3][7] = '#';
	h->look[3][8] = '#';
	h->look[3][9] = '#';

};
void HouseBuilderB::buildpipe()
{
	h->look[6][11] = '#';
};

House* HouseDirector::createHouse(House& house) 
{
	house.createhome();
	house.buildch();
	house.buildwallL();
	house.buildwallR();
	house.buildroof();
	house.buildfloor();
	house.buildwindow();
	house.buildpipe();
	return (house.getHouse());
}