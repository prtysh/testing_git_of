TEMP="temp.mp4"
for file in *.mp4
do
    echo $file
    ffmpeg -i $file -ss 00:10:0.0 -t 15 -an $TEMP
    mv $TEMP $file
done
