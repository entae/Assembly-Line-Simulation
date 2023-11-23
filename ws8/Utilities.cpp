// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.
		for (size_t i = 0; i < allProfiles.size(); i++) {

			// Check if bannedProfile
			bool isBanned = false;
			for (size_t j = 0; j < bannedProfiles.size() && !isBanned; j++) {
				if (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
					allProfiles[i].m_age == bannedProfiles[j].m_age) {
						isBanned = true;
					}
			}

			// add to result if not banned
			if (!isBanned) {
				// copy Profile into new dynamic memory
				Profile* newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);

				// Validate address
				try {
					newProfile->validateAddress();
				} catch (const std::string& msg) {
					delete newProfile;
					throw msg;
				}
				result += newProfile;
				delete newProfile;
			}
		}

		return result;
	}

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Smart Pointers.
		for (size_t i = 0; i < allProfiles.size(); i++) {

			// Check if bannedProfile
			bool isBanned = false;

			for (size_t j = 0; j < bannedProfiles.size() && !isBanned; j++) {
				if (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
					allProfiles[i].m_age == bannedProfiles[j].m_age) {
						isBanned = true;
					}
			}

			// add to result if not banned
			if (!isBanned) {
                std::unique_ptr<Profile> newProfile(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

                try {
                    newProfile->validateAddress();
                } catch (const std::string& msg) {
                    throw msg;
                }

                result += newProfile.get();
            }
        }

		return result;
	}

} // namespace sdds
