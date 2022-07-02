#Windows
convert logo.png -resize 16x16   -depth 32 16-32.png
convert logo.png -resize 32x32   -depth 32 32-32.png
convert logo.png -resize 48x48   -depth 32 48-32.png
convert logo.png -resize 256x256 -depth 32 256-32.png
convert logo.png -resize 512x512 -depth 32 512-32.png

convert 16-32.png 32-32.png 48-32.png 256-32.png 512-32.png MapleTracker.ico

#Mac
mkdir MapleTracker.iconset           
sips -z 16 16     Icon1024.png --out MapleTracker.iconset/icon_16x16.png
sips -z 32 32     Icon1024.png --out MapleTracker.iconset/icon_16x16@2x.png
sips -z 32 32     Icon1024.png --out MapleTracker.iconset/icon_32x32.png
sips -z 64 64     Icon1024.png --out MapleTracker.iconset/icon_32x32@2x.png
sips -z 128 128   Icon1024.png --out MapleTracker.iconset/icon_128x128.png
sips -z 256 256   Icon1024.png --out MapleTracker.iconset/icon_128x128@2x.png
sips -z 256 256   Icon1024.png --out MapleTracker.iconset/icon_256x256.png
sips -z 512 512   Icon1024.png --out MapleTracker.iconset/icon_256x256@2x.png
sips -z 512 512   Icon1024.png --out MapleTracker.iconset/icon_512x512.png
cp Icon1024.png MapleTracker.iconset/icon_512x512@2x.png

iconutil -c icns MapleTracker.iconset