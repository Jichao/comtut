#pragma once

class RegistryManager
{
public:
	RegistryManager();
	~RegistryManager();

	void registry(HINSTANCE hInst, UINT resId);
	void unregistry(HINSTANCE hInst, UINT resId);

private:
};

