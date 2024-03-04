#include "user.h"

user::user()
{
}

user::user(string name, string telephone, string address)
	:name(name),telephone(telephone),address(address)
{
}

user user::FromString(const string& str)
{
	user p;
	stringstream ss(str);
	ss >> p.name >> p.telephone >> p.address;

	return p;
}
