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

#include "replacement.h"
#include "latex.h"

int main(int argc, char **argv)
{
    printf("Testing Equipment replacement...\n\n");

    /* Create context */
    replacement_context* c = replacement_context_new(5, 3);
    if(c == NULL) {
        printf("Unable to create  Equipment replacement's "
               "context... exiting.\n");
        return(-1);
    }

    float* mt = c->manteinance;
    float* s = c->sale_cost;
    float* e= c->equipment_cost;

        /* Set manteinance  cost */
    e[0] = 500;
    e[1] = 500;
    e[2] = 500;
    e[3] = 500;
    e[4] = 500;

    /* Set manteinance  cost */
    mt[0] = 30;
    mt[1] = 40;
    mt[2] = 60;

    /* Set sale cost */
    s[0] = 400;
    s[1] = 300;
    s[2] = 250;

    /* Run algorithm */
    bool success = replacement(c);
    if(!success) {
        printf("Equipment replacement's algorithm was "
               "unable to complete... exiting.\n");
        return(-2);
    }

    /* Show result */
    float* mc = c->minimum_cost;
    for(int i = 0; i <= c->years_plan; i++) {
        printf("G( %d ): %4.2f \n", i, mc[i]);
    }

    /* Generate report */
    bool report_created = replacement_report(c);
    if(!report_created) {
        printf("ERROR: Report could not be created.\n");
    } else {
        printf("Report created at reports/replacement.tex\n");

        int as_pdf = latex2pdf("replacement", "reports");
        if(as_pdf == 0) {
            printf("PDF version available at reports/replacement.pdf\n");
        } else {
            printf("ERROR: Unable to convert report to PDF. Status: %i.\n",
                   as_pdf);
        }
    }


     /* Free resources */
    replacement_context_free(c);
    return(0);
}

