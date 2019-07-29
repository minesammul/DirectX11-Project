#pragma once
class Entity
{
private:
	std::wstring m_wstrName;

public:
	Entity();
	virtual ~Entity();

public:
	virtual Entity* Clone() = 0;

	const std::wstring& GetName()
	{
		return m_wstrName;
	}

	void SetName(const std::wstring& param_strName)
	{
		m_wstrName = param_strName;
	}
};

