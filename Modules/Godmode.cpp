#include "Godmode.h"

#include "../ElDorito.h"

#include <Windows.h>
#include <iostream>

Godmode::Godmode() : enabled(false)
{
}

Godmode::~Godmode()
{
}

std::string Godmode::Info()
{
	std::string Info = "Godmode: ";
	Info += (enabled ? "Enabled" : "Disabled");
	Info += "\nUsage: " + Usage();
	Info += "\nEnables godmod, scripted deaths still occur(such as falling)\n";
	return Info;
}

std::string Godmode::Usage()
{
	return "god (on|off)";
}

void Godmode::Tick(const std::chrono::duration<double>& Delta)
{
}

bool Godmode::Run(const std::vector<std::string>& Args)
{
	const size_t OffsetHealth = 0x7555DC;
	const uint8_t god[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	const uint8_t resetHealth[] = { 0xF3, 0x0F, 0x11, 0x97, 0x00, 0x01, 0x00, 0x00 };

	if( Args.size() >= 2 )
	{
		if( Args[1].compare("off") == 0 )
		{
			std::cout << "Disabling god" << std::endl;
			enabled = false;
			Pointer::Base()(OffsetHealth).Write(resetHealth, sizeof(resetHealth));
		}
		else if( Args[1].compare("on") == 0 )
		{
			std::cout << "Enabling god" << std::endl;
			enabled = true;
			Pointer::Base()(OffsetHealth).Write(god, sizeof(god));
		}
	}

	return false;
}
