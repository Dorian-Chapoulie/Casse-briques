#pragma once
#include "IControler.h"
#include "Bar.h"

class KeyboardManager : IControler {

public:
	KeyboardManager(Bar& bar);
	void checkKeys() const override;

private:
	Bar& bar;
};

