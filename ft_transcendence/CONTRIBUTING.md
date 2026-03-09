# Contributing Guide

## General Guidelines

- **Code Structure:**
  - Backend code is in `auth/` and `database/` (Node.js/Fastify, JavaScript).
  - Frontend code is in `frontend/src/` (TypeScript).
  - Organize new files by feature/module and keep related logic together.

- **Naming Conventions:**
  - Use lowerCamelCase for variables and functions.
  - Use PascalCase for class names.
  - File names: use kebab-case or lowerCamelCase (e.g., `user.js`, `main.ts`).
  - Branch names: use `feature/`, `fix/`, or `refactor/` prefixes as described below.

- **Code Style:**
  - Indent with tabs (backend) or 2 spaces (frontend, if using Prettier/ESLint).
  - Prefer `const`/`let` over `var`.
  - Use async/await for asynchronous code.
  - Add JSDoc/TSDoc comments for exported functions when possible.

- **Commits & PRs:**
  - Write clear, descriptive commit messages.
  - Reference issues or features in PRs.

- **Testing:**
  - If you add or modify features, include or update tests if available.

- **Tracking Bugs and Pending Work:**
  - If you find a bug, technical debt, or something to review later, add a note to `TODO.md` in the project root.

## Branch Structure

```
main        → Stable, production-ready code (DO NOT push directly)
  └── dev   → Integration branch (DO NOT push directly)
        └── feature/* / fix/* / refactor/* → Your working branches
```

## Git Workflow

The idea is to have a "main" safe version, a "dev" working version and create branches to work every time and merge them into "dev" once we are done.
At the moment the repository is on GitHub with some special rules, so that it will require manual reviews to merge into main and dev and they will not accept any push.

### 1. Start new work

Always branch from `dev`:
At the moment main is the default branch so change to dev before starting the new branch.
Is working in the final `prod` branch, same rules, jsut use `prod` instead of `dev`

```bash
git checkout dev
git pull origin dev
git checkout -b feature/your-feature-name
```

This ensures your branch is up to date and based on `dev`.

### 2. Make your changes

Work on your branch, commit often:

```bash
git add .
git commit -m "descriptive message"
```

Remember that not every commit needs a push; you can keep working with commits to establish points and then push when you are done.

### 3. Push your branch

```bash
git push -u origin feature/your-feature-name
```

### 4. Create a Pull Request

Once you have pushed, go to GitHub and request a review.
This request will be put by default in "main"; change it to "dev".

1. Go to GitHub → Pull Requests → New Pull Request
2. Set **base:** `dev` ← **compare:** `your-branch`
3. Add a clear title and description
4. Request a reviewer

You will have to actively request a reviewer in the side menu. You can select as many as you want; you will need 1 review for dev and 2 for main.

### 5. After approval

Once approved, click "Merge pull request" on GitHub.

### 6. Cleaning

Once done, you can continue using your branch to work.
You can also delete it and create a new one if you are using a more strict naming convention.
Try to delete branches that are not being used anymore.

**Important:** Local and remote branches are separate. You need to delete both if the branch exists in both places.

Delete your local branch:

```bash
git branch -d feature/your-feature-name
```

If the branch hasn't been merged and you want to force delete:

```bash
git branch -D feature/your-feature-name
```

Delete the remote branch (on GitHub):

```bash
git push origin --delete feature/your-feature-name
```

To delete both local and remote in one go:

```bash
git branch -d feature/your-feature-name && git push origin --delete feature/your-feature-name
```

Clean up references to deleted remote branches:

```bash
git fetch --prune
```

### 7. Syncing with `dev` and Resolving Conflicts

Before pushing or opening a Pull Request, always update your branch with the latest changes from `dev`. This keeps the codebase clean and avoids merge issues later.

**Steps:**

1. **Update your local `dev` branch:**
   ```bash
   git checkout dev
   git pull origin dev
   ```
2. **Switch back to your working branch:**
   ```bash
   git checkout feature/your-feature
   ```
3. **Integrate changes from `dev`:**
   - To **merge**:
     ```bash
     git merge dev
     ```
   - To **rebase** (recommended for a cleaner history):
     ```bash
     git rebase dev
     ```
4. **Resolve any conflicts:**
   - Git will mark files with conflicts. Open each conflicted file and decide which changes to keep.
   - To keep your version of a file:
     ```bash
     git checkout --ours path/to/file
     ```
   - To keep the version from `dev`:
     ```bash
     git checkout --theirs path/to/file
     ```
   - After resolving, add the files:
     ```bash
     git add path/to/file
     ```
   - For **merge**: commit the resolution:
     ```bash
     git commit
     ```
   - For **rebase**: continue the rebase:
     ```bash
     git rebase --continue
     ```
5. **Push your updated branch:**
   ```bash
   git push origin feature/your-feature
   ```

> **Tip:** If there is an error with unrelated histories, you can force with:
> ```bash
> git merge dev --allow-unrelated-histories
> ```

> **Tip:** Use `git status` to see which files need attention during a conflict. Repeat the conflict resolution steps for each file as needed.

This process is required by our workflow to keep the codebase healthy and avoid merge issues in Pull Requests.

---

## Branch Naming Convention

Please use the following branch naming conventions for clarity and consistency:

| Type        | Format                | Example                |
|-------------|-----------------------|------------------------|
| New feature | `feature/description` | `feature/user-login`   |
| Bug fix     | `fix/description`     | `fix/login-error`      |
| Refactor    | `refactor/description`| `refactor/auth-service`|

---

## Rules

- ❌ Never push directly to `main` or `dev`
- ✅ Always create a Pull Request
- ✅ Always get at least 1 approval before merging
- ✅ Always pull latest `dev` before creating a new branch
- ✅ Always update your banch up to latest `dev` before merging into it
- ✅ Delete branches after merging to keep the repo clean

---

## Questions?

If you have any questions or are unsure about any part of the process, please contact lcuevas-
