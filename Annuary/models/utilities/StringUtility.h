#pragma once
#include <string>

namespace StringUtility
{
	/**
	 * \brief Remove the spaces at the beginning of the string.
	 * \param s The string to trim.
	 * \return The string without spaces at the beginning.
	 */
	std::string ltrim(const std::string& s);
	/**
	 * \brief Remove the spaces at the end of the string.
	 * \param s The string to trim.
	 * \return The string without spaces at the end.
	 */
	std::string rtrim(const std::string& s);
	/**
	 * \brief Remove the spaces at the beginning and at the end of the string
	 * \param s The string to trim
	 * \return The trimmed string
	 */
	std::string trim(const std::string& s);
}

