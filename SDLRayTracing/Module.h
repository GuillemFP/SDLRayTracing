#ifndef MODULE_H
#define MODULE_H

#include "Globals.h"

class Module
{
public:
	Module(const char* name, bool active = true) : name(name), active(active) {}

	virtual ~Module() = default;

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (!active)
		{
			active = Start();
			if (!active)
				LOG("Module unable to start correctly: %s ---", name);
			return active;
		}
		else
		{
			LOG("Module already active: %s --------------", name);
			return true;
		}

		return true;
	}

	bool Disable()
	{
		if (active)
		{
			active = !CleanUp();
			if (active)
				LOG("Module unable to cleanup correctly: %s -", name);
			return !active;
		}
		else
		{
			LOG("Module already disabled: %s ------------", name);
			return true;
		}

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

public:
	const char* name = "";

private:
	bool active = true;
};

#endif // !MODULE_H