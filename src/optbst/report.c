/*
 * Copyright (C) 2012 Carolina Aguilar <caroagse@gmail.co.cr>
 * Copyright (C) 2012 Carlos Jenkins <carlos@jenkins.co.cr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "report.h"

bool optbst_report(optbst_context* c)
{
    /* Create report file */
    FILE* report = fopen("reports/optbst.tex", "w");
    if(report == NULL) {
        return false;
    }

    /* Write preamble */
    bool success = insert_file("latex/header.tex", report);
    if(!success) {
        return false;
    }
    fprintf(report, "\n");

    /* Write header */
    fprintf(report, "\\section{%s}\n\n", "Optimal Binary Search Trees");
    fprintf(report, "\\noindent{\\huge %s.} \\\\[0.4cm]\n",
                    "Dynamic programming");
    fprintf(report, "{\\LARGE %s.}\\\\[0.4cm]\n", "Operation Research");
    fprintf(report, "\\HRule \\\\[0.5cm]\n");

    /* Write description */
    fprintf(report, "\\indent ");
    success = insert_file("latex/optbst.txt", report);
    if(!success) {
        return false;
    }

    /* Write first section */
    fprintf(report, "\\\\[0.5cm]\n\\noindent{\\Large Details:}\n");
    fprintf(report, "\\begin{compactitem}\n");
    fprintf(report, "\\item %s : \\textsc{%s}. \n",
                    "Executed on", get_current_time());
    fprintf(report, "\\item %s : \\textsc{%lf %s}. \n",
                    "Execution time", c->execution_time,
                    "seconds");
    fprintf(report, "\\item %s : \\textsc{%i %s}. \n",
                    "Memory required", c->memory_required,
                    "bytes");
    fprintf(report, "\\end{compactitem}\n");
    fprintf(report, "\n");

    /* TOC */
    fprintf(report, "\\newpage\n\\tableofcontents\n\\newpage\n");
    fprintf(report, "\n");

    optbst_graph(c);

    /* End document */
    fprintf(report, "\n");
    fprintf(report, "\\end{document}");

    /* Save & swap buffers */
    int success_file = fflush(report);
    if(success_file == EOF) {
        return false;
    }
    success_file = fclose(c->report_buffer);
    if(success_file == EOF) {
        return false;
    }
    c->report_buffer = report;

    return true;
}

void find_lnodes(matrix* r, int i, int j, FILE* stream)
{
    /* Current node, search node */
    int cn = (int)r->data[i][j];
    int sn = cn;

    /* Search node */
    for(; cn == sn && j > -1; j--) {
        sn = (int)r->data[i][j];
    }

    /* No childs */
    if(sn == 0) {
        return;
    }

    /* Write node found and continue */
    fprintf(stream, "    %i -> %i;\n", cn, sn);
    find_lnodes(r, i, j, stream);
    find_rnodes(r, i, j, stream);
}

void find_rnodes(matrix* r, int i, int j, FILE* stream)
{
    /* Current node, search node */
    int cn = (int)r->data[i][j];
    int sn = cn;

    /* Search node */
    for(; cn == sn && i < r->rows; i++) {
        sn = (int)r->data[i][j];
    }

    /* No childs */
    if(sn == 0) {
        return;
    }

    /* Write node found and continue */
    fprintf(stream, "    %i -> %i;\n", cn, sn);
    find_lnodes(r, i, j, stream);
    find_rnodes(r, i, j, stream);
}

void optbst_graph(optbst_context* c)
{
    /* Create tree file */
    FILE* tree = fopen("reports/tree.gv", "w");
    if(tree == NULL) {
        return;
    }

    /* Preamble */
    fprintf(tree, "digraph bstree {\n\n");
    fprintf(tree, "    node [shape = circle];\n");
    fprintf(tree, "    graph [ordering=\"out\"];\n\n");

    /* Labels */
    for(int i = 0; i < c->keys; i++) {
        char* name = c->names[i];
        fprintf(tree, "    %i [label = \"%s\"];\n", i + 1, name);
    }
    fprintf(tree, "\n");

    /* Vertices */
    int i = 0;
    int j = c->table_r->columns - 1;
    find_lnodes(c->table_r, i, j, tree);
    find_rnodes(c->table_r, i, j, tree);
    fprintf(tree, "\n");
    fprintf(tree, "}\n");

    /* Close file */
    fclose(tree);

    /* Render graph */
    gv2pdf("tree", "reports");
}
