pandoc --template algo --filter ./pandoc/minted.py --pdf-engine=xelatex --no-highlight --pdf-engine-opt="-shell-escape" -o template.tex --from markdown -V mainfont="Source Han Serif CN" -V monofont="Source Code Pro" -V sansfont="Source Han Sans CN" -V CJKmainfont="Source Han Serif CN" -V secnumdepth=2 -V --number-sections --toc -V include-before="\renewcommand\labelitemi{$\bullet$}" -V header-includes="\usepackage{minted}" -V geometry="margin=2cm" *-*.md
latexmk -xelatex -shell-escape template.tex
latexmk -c
