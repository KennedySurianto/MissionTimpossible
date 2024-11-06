# Unreal Engine Project Setup After `git pull`

After performing a `git pull`, if you encounter missing files or issues (especially on a fresh environment or a different machine), follow these steps to restore or regenerate necessary files.

## 1. Regenerate Project Files

To generate Visual Studio project files (or the equivalent for your development environment):
1. Right-click on the `.uproject` file.
2. Select **Generate Visual Studio project files**.

This will regenerate all the necessary project files based on the current source code.

## 2. Rebuild Binaries and Intermediate Files

If your `.gitignore` excludes binaries and intermediate files, they will need to be rebuilt:
1. Open the project in Unreal Engine or Visual Studio.
2. Perform a build. Unreal Engine will automatically regenerate these files as needed.

## 3. Restore Derived Data Cache

If asset files (like textures) are missing or appear unoptimized:
1. Ensure that the **DerivedDataCache/** folder is clear.
2. Open the project in Unreal Engine, and it will regenerate the Derived Data Cache automatically.

> **Tip**: If there are issues, try manually deleting the `DerivedDataCache/` folder before reopening Unreal Engine.

## 4. Editor Settings

Certain editor settings are user-specific and may not be included in source control. If specific settings are essential:
- Recreate these settings manually in the Unreal Engine Editor, or
- Coordinate with team members to share the necessary configurations outside of Git.

---

This guide should help ensure your project is fully set up and running after pulling the latest changes. For additional setup or troubleshooting tips, please refer to Unreal Engine’s documentation or your team’s setup guidelines.
