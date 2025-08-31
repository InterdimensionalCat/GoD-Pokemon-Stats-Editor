#pragma once

class ProjectRoot
{

public:

	ProjectRoot() = default;

	void SetProjectRootPath();

	void CloseCurrentRoot();

	void OnProjectRootPathSet();

	std::filesystem::path GetProjectRootPath();

	bool IsProjectRootSet();

	static std::shared_ptr<ProjectRoot> Get();

private:

	bool bProjectRootPathSet = false;

	std::filesystem::path ProjectRootPath;

};
