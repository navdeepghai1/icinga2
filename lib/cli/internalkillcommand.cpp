/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2018 Icinga Development Team (https://www.icinga.com/)  *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "cli/internalkillcommand.hpp"
#include <signal.h>

using namespace icinga;
namespace po = boost::program_options;

REGISTER_CLICOMMAND("internal/kill", InternalKillCommand);

String InternalKillCommand::GetDescription() const
{
	return "Tries to kill a PID";
}

String InternalKillCommand::GetShortDescription() const
{
	return "Tries to kill a PID";
}

ImpersonationLevel InternalKillCommand::GetImpersonationLevel() const
{
    return ImpersonateIcinga;
}

bool InternalKillCommand::IsHidden() const
{
	return true;
}

void InternalKillCommand::InitParameters(boost::program_options::options_description& visibleDesc,
	boost::program_options::options_description& hiddenDesc) const
{
	visibleDesc.add_options()
		("pid,p", po::value<int>(), "PID to kill")
		("sig,s", po::value<String>(), "Signal (POSIX string) to send")
	;
}

/**
 * The entry point for the "internal kill" CLI command.
 *
 * @returns An exit status.
 */
int InternalKillCommand::Run(const boost::program_options::variables_map& vm, const std::vector<std::string>& ap) const
{
	String signal = vm["sig"].as<String>();

	/* Thank POSIX */
	if (signal == "SIGKILL")
		return kill(vm["pid"].as<int>(), SIGKILL);
	if (signal == "SIGINT")
		return kill(vm["pid"].as<int>(), SIGINT);
	if (signal == "SIGCHLD")
		return kill(vm["pid"].as<int>(), SIGCHLD);

	return 1;
}

