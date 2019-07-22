#pragma once
class Entity
{
private:
	std::string m_strName;

public:
	Entity();
	virtual ~Entity();

public:
	const std::string& GetName()
	{
		return m_strName;
	}

	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}
};

