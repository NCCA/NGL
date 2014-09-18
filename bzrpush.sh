bzr push sftp://nccastaff.bournemouth.ac.uk/home/ncca/public_html/jmacey/Code/NGL

bzr log -l 1 &>version.txt

scp version.txt nccastaff.bmth.ac.uk:/home/ncca/public_html/jmacey/GraphicsLib
bzr log &>fullhistory.txt
scp fullhistory.txt nccastaff.bmth.ac.uk:/home/ncca/public_html/jmacey/GraphicsLib