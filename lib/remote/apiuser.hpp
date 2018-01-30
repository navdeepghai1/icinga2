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

#ifndef APIUSER_H
#define APIUSER_H

#include "remote/i2-remote.hpp"
#include "remote/apiuser-ti.hpp"

namespace icinga
{

/**
 * @ingroup remote
 */
class ApiUser final : public ObjectImpl<ApiUser>
{
public:
	DECLARE_OBJECT(ApiUser);
	DECLARE_OBJECTNAME(ApiUser);

	virtual void OnConfigLoaded(void) override;

	static ApiUser::Ptr GetByClientCN(const String& cn);
	static String CreateHashedPasswordString(const String& password, const String& salt, const bool shadow = false);

	Dictionary::Ptr GetPasswordDict(void) const;
	bool ComparePassword(String password) const;
};

}

#endif /* APIUSER_H */
