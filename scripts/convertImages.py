import os
import json
from PIL import Image

# Path to the songs directory and songs.json
directory = "/home/vanitas/Work/Projects/Songer/covers"
json_path = os.path.join(directory, "../assets/songs.json")

# Convert all .webp images to .png
converted_files = {}
for filename in os.listdir(directory):
    if filename.lower().endswith(".webp"):
        webp_path = os.path.join(directory, filename)
        png_filename = os.path.splitext(filename)[0] + ".png"
        png_path = os.path.join(directory, png_filename)

        try:
            with Image.open(webp_path) as img:
                img.save(png_path, "PNG")
                print(f"Converted: {webp_path} -> {png_path}")
                converted_files[filename] = png_filename
                os.remove(webp_path)
                print(f"Deleted: {webp_path}")
        except Exception as e:
            print(f"Failed to convert {webp_path}: {e}")

# Update songs.json if conversion succeeded
if os.path.exists(json_path):
    with open(json_path, "r", encoding="utf-8") as f:
        data = json.load(f)

    updated = False
    for song in data:
        image_path = song.get("image", "")
        image_filename = os.path.basename(image_path)
        if image_filename in converted_files:
            new_image_path = image_path.replace(image_filename, converted_files[image_filename])
            song["image"] = new_image_path
            updated = True
            print(f"Updated JSON path: {image_path} -> {new_image_path}")

    if updated:
        with open(json_path, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=4)
            print("Updated songs.json successfully.")
    else:
        print("No paths in songs.json needed updating.")
else:
    print("songs.json not found.")
