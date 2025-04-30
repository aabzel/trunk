#include "vector_diag.h"

#include <stdio.h>
#include <string.h>

#include "float_utils.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "vector_math.h"
#include "writer_config.h"

void print_line(Line_t line, char* in_text) {
    print_dot(line.start, in_text);
    print_vector(line.vector, in_text);
}

void print_dot(Dot_t d, char* in_text) { LOG_INFO(MATH, "%s D[%f, %f, %f]", in_text, d.x, d.y, d.z); }

const char* VectorToStr(const Vector_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s(dx:%f,", text, Node->dx);
        snprintf(text, sizeof(text), "%sdy:%f,", text, Node->dy);
        snprintf(text, sizeof(text), "%sdz:%f)", text, Node->dz);
    }
    return text;
}

const char* VectorFtoStr(const VectorF_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sdx:%6.2f,", text, Node->dx);
        snprintf(text, sizeof(text), "%sdy:%6.2f,", text, Node->dy);
        snprintf(text, sizeof(text), "%sdz:%6.2f", text, Node->dz);
    }
    return text;
}

void print_vector(Vector_t v, char* in_text) { LOG_INFO(MATH, "%s%s", in_in_text, VectorToStr(&v)); }

#define VEC_LIM 1.0
#define VEC_STEP 0.5

static const char* FalseToDiff(bool equal) {
    const char* name = "?";
    switch((uint8_t)equal) {
    case true:
        name = "Same";
        break;
    case false:
        name = "Diff";
        break;
    }
    return name;
}

bool math_vector_angle_diag(char* key_word1, char* key_word2) {
    bool res = false;
    uint32_t num = 0;
    uint32_t ok = 0;
    Vector_t V1 = {0};
    Vector_t V2 = {0};

    static const table_col_t cols[] = {
        {5, "No"}, {12, "A"}, {12, "B"}, {8, "angleTr"}, {8, "angleNa"}, {6, "diff"}, {5, "|A|"}, {5, "|B|"},
    };
    char log_line[150] = {0};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(V1.dx = -VEC_LIM; V1.dx <= VEC_LIM; V1.dx += VEC_STEP) {
        for(V1.dy = -VEC_LIM; V1.dy <= VEC_LIM; V1.dy += VEC_STEP) {

            for(V2.dx = -VEC_LIM; V2.dx <= VEC_LIM; V2.dx += VEC_STEP) {
                for(V2.dy = -VEC_LIM; V2.dy <= VEC_LIM; V2.dy += VEC_STEP) {
                    double angle_deg = calc_angle_between_vectors_deg(&V1, &V2);
                    double angle_naiv_deg = calc_fll_discriminator_deg(&V1, &V2);
                    res = is_double_equal_absolute(angle_naiv_deg, angle_deg, 0.001);
                    strcpy(log_line, TSEP);

                    snprintf(log_line, sizeof(log_line), "%s %4.1f, %4.1f " TSEP, log_line, V1.dx, V1.dy);
                    snprintf(log_line, sizeof(log_line), "%s %4.1f, %4.1f " TSEP, log_line, V2.dx, V2.dy);
                    snprintf(log_line, sizeof(log_line), "%s %6.1f " TSEP, log_line, angle_deg);
                    snprintf(log_line, sizeof(log_line), "%s %6.1f " TSEP, log_line, angle_naiv_deg);
                    snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, FalseToDiff(res));
                    snprintf(log_line, sizeof(log_line), "%s %3.1f " TSEP, log_line, norm_d(&V1));
                    snprintf(log_line, sizeof(log_line), "%s %3.1f " TSEP, log_line, norm_d(&V2));
                    // cli_printf("%s" CRLF, log_line);
                    res = is_contain(log_line, key_word1, key_word2);
                    if(res) {
                        cli_printf(TSEP " %3u ", num);
                        cli_printf("%s" CRLF, log_line);
                        // cli_printf(CRLF);
                        num++;
                        ok++;
                    }
                    // cli_printf(CRLF);
                }
            }
        }
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
