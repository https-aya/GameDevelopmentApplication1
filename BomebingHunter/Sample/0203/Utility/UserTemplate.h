#pragma once

template <typename T>

//��Βl�ɕϊ�
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		result = value;
	}
	else
	{
		result = -value;
	}

	return result;
}

template <typename T>
//�ő�l��Ԃ�
T Max(T a, T b)
{
	T result;

	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}

template <typename T>
//�ŏ��l��Ԃ�
T Min(T a, T b)
{
	T result;

	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}