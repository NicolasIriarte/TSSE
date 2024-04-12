# Build tex files into a PDF.
tp1:
    #!/bin/bash
    set -e
    cd {{justfile_directory()}}/TP1
    pdflatex -shell-escape \\nonstopmode\\input Tp1-IriarteNicolas.tex || echo "First compilation failed."

tp2:
    #!/bin/bash
    cd {{justfile_directory()}}/TP2
    ceedling

tp4:
    #!/bin/bash
    cd {{justfile_directory()}}/TP4
    ceedling gcov:all utils:gcov

tp5:
    #!/bin/bash
    cd {{justfile_directory()}}/TP5
    pdflatex -shell-escape \\nonstopmode\\input Tp5-IriarteNicolas.tex || echo "First compilation failed."

# Clean repository.
clean:
    #!/bin/bash
    rm -rf */*.aux */*.log */*.out */*.toc */*.pdf */build
