# BrowserSync — Drive Backup Extension

Backs up your **bookmarks**, **history**, and **extension list** to a `BrowserSync_Backup/` folder on your Google Drive. Works on **Chromium/Brave** and **Firefox**.

---

## What it syncs

| Data | Backed up | Restored |
|------|-----------|----------|
| Bookmarks | ✅ Full tree | ✅ Imports into new folder |
| History | ✅ Last 30 days | ℹ️ Export only (browser API can't write history) |
| Extension list | ✅ Name + store link | ✅ Shows install links |
| Passwords | ❌ | Use browser's built-in export (Settings → Passwords → Export) |

> **Passwords** can't be accessed by extensions for security reasons. Export manually from browser settings and upload to Drive yourself.

---

## Setup — Step by step

### 1. Get a Google OAuth Client ID

This is a one-time setup. You need this for Google Drive access.

1. Go to https://console.cloud.google.com/
2. Create a new project (e.g., `BrowserSync`)
3. Go to **APIs & Services → Library** → enable **Google Drive API**
4. Go to **APIs & Services → Credentials → Create Credentials → OAuth 2.0 Client ID**
5. Choose:
   - For **Chromium/Brave**: Application type = `Chrome Extension`
     - Enter your extension ID (you get this after loading it in step 2)
   - For **Firefox**: Application type = `Web Application`
     - Add redirect URI: `https://<your-extension-id>.extensions.allizom.org/`
     - Get this from `browser.identity.getRedirectURL()` in the browser console
6. Copy the **Client ID**

### 2. Set your Client ID

Open `background.js` and replace:
```
YOUR_GOOGLE_OAUTH_CLIENT_ID.apps.googleusercontent.com
```
with your actual client ID.

**For Chromium**, also update `manifest-chromium.json`:
```json
"oauth2": {
  "client_id": "YOUR_CLIENT_ID_HERE.apps.googleusercontent.com",
  ...
}
```

### 3. Install the extension

#### Chromium / Brave
1. Rename `manifest-chromium.json` → `manifest.json`
2. Open `brave://extensions` or `chrome://extensions`
3. Enable **Developer mode** (top right)
4. Click **Load unpacked** → select the `browser-sync-ext/` folder
5. Note your extension ID from the extensions page
6. Go back to Google Cloud Console → update the Chrome Extension ID

#### Firefox
1. Rename `manifest-firefox.json` → `manifest.json`
2. Open `about:debugging#/runtime/this-firefox`
3. Click **Load Temporary Add-on** → select `manifest.json`
4. *(For permanent install, you need to sign it via addons.mozilla.org)*

---

## Usage

Click the extension icon in your toolbar:

- **☁ Backup everything now** — uploads bookmarks, history (30 days), extension list to Drive
- **🔖 Bookmarks** — restores bookmarks from Drive into a dated folder
- **🧩 Extensions** — shows your backed-up extension list with "Install →" links
- **Auto-backup toggle** — runs a backup automatically when browser starts (max once/24h)

---

## Drive folder structure

```
My Drive/
└── BrowserSync_Backup/
    ├── bookmarks.json
    ├── history.json
    ├── extensions_chromium.json
    └── extensions_firefox.json
```

Chromium and Firefox each write their own `extensions_*.json` file, so you get both lists.

---

## Notes

- Bookmarks are **imported into a new folder** (not replacing existing ones) to avoid accidental data loss
- History export is informational only — browsers don't allow extensions to import history
- Re-running backup **overwrites** the previous files on Drive (no versioning by default — Drive's version history handles that)
- The extension only requests `drive.file` scope, which means it can only access files it created itself — it won't see your other Drive content
