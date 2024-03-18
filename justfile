# Build tex files into a PDF.
tp1:
    #!/bin/bash
    set -e
    #######
    # TP1 #
    #######
    # cd plantuml
    # plantuml *.puml
    # mv *.png ../assets/
    cd {{justfile_directory()}}/TP1
    pdflatex -shell-escape \\nonstopmode\\input Tp1-IriarteNicolas.tex || echo "First compilation failed."
    # pdflatex -shell-escape \\nonstopmode\\input Tp1-IriarteNicolas.tex || echo "Second compilation failed."
    # pdflatex -shell-escape \\nonstopmode\\input Tp1-IriarteNicolas.tex

    #######
    # TP2 #
    #######

    # cd {{justfile_directory()}}/TP2
    # cd plantuml

    # plantuml *.puml
    # mv *.png ../Figuras/

    # cd ..
    # pdflatex -shell-escape \\nonstopmode\\input Tp2-IriarteNicolas.tex || echo "First compilation failed."
    # # pdflatex -shell-escape \\nonstopmode\\input Tp2-IriarteNicolas.tex || echo "Second compilation failed."
    # # pdflatex -shell-escape \\nonstopmode\\input Tp2-IriarteNicolas.tex

    #######
    # TP3 #
    #######

    # cd {{justfile_directory()}}/TP3
    # cd plantuml

    # plantuml *.puml
    # mv *.png ../Figuras/

    # cd ..
    # pdflatex -shell-escape \\nonstopmode\\input Tp3-IriarteNicolas.tex || echo "First compilation failed."
    # # pdflatex -shell-escape \\nonstopmode\\input Tp3-IriarteNicolas.tex || echo "Second compilation failed."
    # # pdflatex -shell-escape \\nonstopmode\\input Tp3-IriarteNicolas.tex

tp2:
    #!/bin/bash
    cd {{justfile_directory()}}/TP2
    ceedling


# Clean repository.
clean:
    #!/bin/bash
    rm -rf */*.aux */*.log */*.out */*.toc */*.pdf */build
