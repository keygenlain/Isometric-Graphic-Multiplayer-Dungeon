#pragma once

#include <SFML/Network.hpp>
#include <string>
#include <functional>

namespace IsometricMUD {

/**
 * @brief Update information
 */
struct UpdateInfo {
    std::string version;
    std::string downloadUrl;
    std::string changelog;
    size_t fileSize;
};

/**
 * @brief Handles game updates
 */
class Updater {
public:
    Updater();
    ~Updater();

    /**
     * @brief Check for updates from server
     */
    bool checkForUpdates(const std::string& updateServerUrl);

    /**
     * @brief Get the latest update information
     */
    UpdateInfo getUpdateInfo() const { return updateInfo; }

    /**
     * @brief Download and install update
     */
    bool downloadUpdate(std::function<void(float)> progressCallback = nullptr);

    /**
     * @brief Check if an update is available
     */
    bool isUpdateAvailable() const { return updateAvailable; }

    /**
     * @brief Get current version
     */
    std::string getCurrentVersion() const { return currentVersion; }

private:
    bool updateAvailable;
    UpdateInfo updateInfo;
    std::string currentVersion;
};

} // namespace IsometricMUD
