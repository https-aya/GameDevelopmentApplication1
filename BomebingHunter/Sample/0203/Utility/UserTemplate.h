#pragma once

template <typename T>

//â‘Î’l‚É•ÏŠ·
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
//Å‘å’l‚ğ•Ô‚·
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
//Å¬’l‚ğ•Ô‚·
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