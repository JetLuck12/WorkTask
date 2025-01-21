#pragma once

#include <exception>

class CollinearExp final : public std::exception
{
	const char* what() const override { return "Segments are collinear"; }
};

class NotIntersect final : public std::exception
{
	const char* what() const override { return "Segments are not intersect"; }
};