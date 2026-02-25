# 🎵 MP3 Tag Reader (C Project)

## 📌 Description

This project implements an **MP3 Tag Reader and Editor** using the **C programming language**.
It allows users to **view and modify ID3 metadata tags** present inside MP3 files.

Using this tool, you can read or update information such as:
- Title
- Artist
- Album
- Track number
- Comments

The project focuses on **binary file handling** and **metadata parsing**, without affecting the actual audio content.

---

## 📂 Project Files

```

MP3_Tag_Reader/
│
├── main.c        # Main driver program
├── view.c        # Logic to view MP3 tags
├── view.h        # View function declarations
├── edit.c        # Logic to edit MP3 tags
├── edit.h        # Edit function declarations
├── type.h        # Common data types and macros
│
├── README.md     # Project documentation

````

---

## ⚙️ Compilation

Compile all source files together using GCC:

```bash
gcc main.c view.c edit.c -o mp3tag
````

This will generate an executable file:

```bash
mp3tag
```

---

## ▶️ How to Run

### 🔍 View MP3 Tags

```bash
./mp3tag -v song.mp3
```

### 🔹 Explanation:

* `-v` → View mode
* `song.mp3` → MP3 file whose tags are to be displayed

---

### ✏️ Edit MP3 Tags

```bash
./mp3tag -e -t "New Title" song.mp3
```

### 🔹 Explanation:

* `-e` → Edit mode
* `-t` → Modify title tag
* `"New Title"` → New value (must be inside double quotes)
* `song.mp3` → Target MP3 file

---

## 🏷 Supported Command-Line Options

| Option | Description            |
| ------ | ---------------------- |
| `-v`   | View MP3 tag details   |
| `-e`   | Edit mode              |
| `-h`   | Display help           |
| `-t`   | Modify Title tag       |
| `-T`   | Modify Track tag       |
| `-a`   | Modify Artist tag      |
| `-A`   | Modify Album tag       |
| `-y`   | Modify Comment tag     |
| `-c`   | Modify TCOM tag        |
| `-C`   | Modify Compression tag |

---

## 🧪 Example Workflow

```bash
gcc main.c view.c edit.c -o mp3tag
./mp3tag -v sample.mp3
./mp3tag -e -a "New Artist" sample.mp3
```

---

## 📌 Important Notes

* Only **MP3 files with ID3 tags** are supported
* Always enclose edited text within **double quotes**
* Do **not** push compiled files (`a.out`) or large `.mp3` files to GitHub
* Recommended to use `.gitignore` for binaries and media files

Example `.gitignore`:

```text
a.out
*.mp3
```

---

## 🎓 Learning Outcomes

This project helps in understanding:

* Binary file structures
* ID3 metadata format
* File pointers and offsets
* Modular programming in C
* Command-line argument handling

---

## 🚀 Future Enhancements

* Support ID3v2 extended frames
* Add validation for corrupted MP3 files
* Support batch processing
* Create a menu-driven or GUI version

---

## 👨‍💻 Author

**Poojith M**
Project – MP3 Tag Reader in C

---

## 📜 License

This project is intended for **academic and educational use**.

---

```
---
If you want next:
- I can **tailor this for college submission**
- Shorten it for **resume GitHub projects**
- Add **screenshots / demo section**
- Improve wording for **viva / interview explanation**
```
