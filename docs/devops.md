# DevOps Documentation

## Release Management

### Creating a Release
1. Ensure your changes are committed and pushed to the main branch
2. Go to GitHub Actions
3. Run the "Release" workflow
4. Choose whether to create as draft
5. The workflow will automatically:
   - Read version from VERSION file
   - Create appropriate tag
   - Generate release notes

### Updating an Existing Release
If you need to update an already published release:

1. Delete the existing release from GitHub interface
2. Delete the tag using these commands:
   ```bash
   # Delete remote tag
   git push --delete origin <tag_name>
   
   # Delete local tag (if it exists)
   git tag -d <tag_name>
   ```
3. Run the release workflow again

### Version Management
- Versions are controlled by the `VERSION` file in the root directory
- Follow semantic versioning (MAJOR.MINOR.PATCH)
- Update the VERSION file before creating a new release

## Release and Tag Management

When dealing with releases and tags, it's important to understand that:

- If you delete a release but keep its tag, creating a new release with the same tag will use the old commit point, not including new changes[1].
- To properly re-release with the same version, you need to:
  1. Delete the release from GitHub interface
  2. Delete the tag both locally and remotely[2]
  3. Create a new release with the same tag
