#pragma once
class Object
{
protected:
	TObjectMatrix m_worldMatrix;
	std::string m_name;

public:
	Object();
	~Object();

	virtual void Update() = 0;

	virtual TObject CreateObject() = 0;

	TObjectMatrix GetWorldMatrix()
	{
		return m_worldMatrix;
	}

	std::string GetName()
	{
		return m_name;
	}
};

