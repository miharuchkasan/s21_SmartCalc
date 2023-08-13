#include "s21_calc.h"

void s21_parcer(char *argv, element **stack) {
  char number_string[] = "1234567890.";
  char function_string[] = "sctalxp(";
  int length = strlen(argv);
  int length_buffer = 257;
  for (int i = 0; i < length; i++) {
    if (strchr(number_string, argv[i]) && argv[i] != '\0') {
      int counter = 0;
      char output_string[length_buffer];
      while (strchr(number_string, argv[i]) && argv[i] != '\0') {
        output_string[counter] = argv[i];
        counter++;
        i++;
      }
      output_string[counter] = '\0';
      push(stack, atof(output_string), 0, NUM);
      output_string[0] = '\0';
      if (strchr(function_string, argv[i]) && argv[i] != '\0') {
        push(stack, 0.0, 2, MUL);
      }
    }

    if (argv[i] == 'c') {
      if (strstr(argv, "cos") != NULL) {
        push(stack, 0.0, 4, COS);
        i += 2;
      }
    }
    if (argv[i] == 's') {
      if (argv[i + 1] == 'i') {
        push(stack, 0.0, 4, SIN);
        i += 2;
      }
      if (argv[i + 1] == 'q') {
        push(stack, 0.0, 4, SQRT);
        i += 3;
      }
    }
    if (argv[i] == 't') {
      if (argv[i + 1] == 'a') {
        push(stack, 0.0, 4, TAN);
        i += 2;
      }
    }
    if (argv[i] == 'a') {
      if (argv[i + 1] == 'c') {
        push(stack, 0.0, 4, ACOS);
        i += 3;
      }
      if (argv[i + 1] == 's') {
        push(stack, 0.0, 4, ASIN);
        i += 3;
      }
      if (argv[i + 1] == 't') {
        push(stack, 0.0, 4, ATAN);
        i += 3;
      }
    }
    if (argv[i] == 'l') {
      if (argv[i + 1] == 'n') {
        push(stack, 0.0, 4, LN);
        i += 1;
      }
      if (argv[i + 1] == 'o') {
        push(stack, 0.0, 4, LOG);
        i += 2;
      }
    }
    if (argv[i] == 'm') {
      if (argv[i + 1] == 'o') {
        push(stack, 0.0, 2, MOD);
        i += 2;
      }
    }
    if (argv[i] == '+') {
      if (argv[i] == '+') {
        if (!i) {
          push(stack, 0.0, 1, NUM);
        }
        push(stack, 0.0, 1, PLUS);
      }
    }
    if (argv[i] == '-') {
      if (!i) {
        push(stack, 0.0, 1, NUM);
      }
      push(stack, 0.0, 1, MINUS);
    }
    if (argv[i] == '*') {
      push(stack, 0.0, 2, MUL);
    }
    if (argv[i] == '/') {
      push(stack, 0.0, 2, DIV);
    }
    if (argv[i] == '^') {
      push(stack, 0.0, 3, EXP);
    }
    if (argv[i] == 'x') {
      push(stack, 0.0, 0, X);
    }
    if (argv[i] == 'p') {
      push(stack, 3.14, 0, PI);
    }
    if (argv[i] == '(') {
      push(stack, 0.0, 5, BRACK_O);
      if (argv[i + 1] == '-' || argv[i + 1] == '+') {
        push(stack, 0.0, 0, NUM);
      }
    }
    if (argv[i] == ')') {
      push(stack, 0.0, 5, BRACK_C);
      if (strchr(function_string, argv[i + 1]) && argv[i + 1] != '\0') {
        push(stack, 0.0, 2, MUL);
      }
    }
  }
}

double r_polish_notation(element **stack) {
  double result = 0;
  element *numbers = {0};
  element *help = {0};
  while ((*stack) != NULL) {
    if ((*stack)->priority == 0) {
      push(&numbers, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 && help == NULL) {
      push(&help, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 &&
               ((*stack)->priority > help->priority || help->type == 18)) {
      push(&help, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 && (*stack)->priority <= help->priority &&
               help->type != 18) {
      while ((*stack)->priority <= help->priority && help->type != 18) {
        push(&numbers, help->value, help->priority, help->type);
        remove_element(&help);
        if (help == NULL || (*stack == NULL)) {
          break;
        }
      }
      push(&help, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type == 19) {
      while (help->type != 18) {
        push(&numbers, help->value, help->priority, help->type);
        remove_element(&help);
      }
      remove_element(&help);
    }
    remove_element(stack);
  }
  while (help != NULL) {
    push(&numbers, help->value, help->priority, help->type);
    remove_element(&help);
  }
  reverse_stack(&numbers, stack);
  result = calculate(stack);
  return result;
}

double calculate(element **stack) {
  double result = 0.0;
  element *help = {0};
  while (*stack != 0) {
    while ((*stack)->priority == 0) {
      push(&help, (*stack)->value, (*stack)->priority, (*stack)->type);
      remove_element(stack);
    }
    if ((*stack)->type == X) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value += tmp;
    } else if ((*stack)->type == PLUS) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value += tmp;
    } else if ((*stack)->type == MINUS) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value -= tmp;
    } else if ((*stack)->type == MUL) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value *= tmp;
    } else if ((*stack)->type == DIV) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value /= tmp;
    } else if ((*stack)->type == MOD) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value = fmod(help->value, tmp);
    } else if ((*stack)->type == EXP) {
      double tmp;
      tmp = help->value;
      remove_element(&help);
      help->value = pow(help->value, tmp);
    } else if ((*stack)->type == COS) {
      help->value = cos(help->value);
    } else if ((*stack)->type == SIN) {
      help->value = sin(help->value);
    } else if ((*stack)->type == TAN) {
      help->value = tan(help->value);
    } else if ((*stack)->type == ACOS) {
      help->value = acos(help->value);
    } else if ((*stack)->type == ASIN) {
      help->value = asin(help->value);
    } else if ((*stack)->type == ATAN) {
      help->value = atan(help->value);
    } else if ((*stack)->type == SQRT) {
      help->value = sqrt(help->value);
    } else if ((*stack)->type == LN) {
      help->value = log(help->value);
    } else if ((*stack)->type == LOG) {
      help->value = log10(help->value);
    }
    result = help->value;
    if (*stack != NULL) {
      remove_element(stack);
    }
  }
  remove_element(&help);
  return result;
}

void push(element **head, double value, int priority, type_t type) {
  element *tmp = (element *)malloc(sizeof(element));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *head;
  *head = tmp;
}

void remove_element(element **head) {
  element *prev = NULL;
  if (head != NULL) {
    prev = *head;
    *head = (*head)->next;
    free(prev);
  }
}

void reverse_stack(element **stack, element **result) {
  while ((*stack) != NULL) {
    push(result, (*stack)->value, (*stack)->priority, (*stack)->type);
    remove_element(stack);
  }
}

int function_check(char *argv, int *point) {
  int asinus_sign = 0;
  int acosinus_sign = 0;
  int atan_sign = 0;
  int log_sign = 0;
  int error_sign = 0;
  int length = strlen(argv);
  int sinus_sign = 0;
  int sqrt_sign = 0;

  int start_point = *point;
  if (argv[start_point] == 's' && start_point < length) {
    if (argv[start_point + 1] == 'i') {
      sinus_sign = sinus_check(argv, start_point + 2);
      if (!sinus_sign) {
        *point = start_point + 3;
      }
    } else if (argv[*point + 1] == 'q') {
      sqrt_sign = sqrt_check(argv, start_point + 2);
      if (!sqrt_sign) {
        *point = start_point + 4;
      }
    } else {
      error_sign = 1;
    }
    if (!error_sign && (sinus_sign ^ sqrt_sign)) {
      error_sign = 1;
    }
  } else if (argv[start_point] == 'c' && start_point < length) {
    error_sign = cosinus_check(argv, start_point + 1);
    if (!error_sign) {
      *point = start_point + 3;
    }
  } else if (argv[start_point] == 't' && start_point < length) {
    error_sign = tan_check(argv, start_point + 1);
    if (!error_sign) {
      *point = start_point + 3;
    }
  } else if (argv[start_point] == 'a' && start_point < length) {
    if (argv[start_point + 1] == 's' && argv[start_point + 2] == 'i') {
      asinus_sign = sinus_check(argv, start_point + 3);
      if (!asinus_sign) {
        *point = start_point + 4;
      }
    } else if (argv[start_point + 1] == 'c') {
      acosinus_sign = cosinus_check(argv, start_point + 2);
      if (!acosinus_sign) {
        *point = start_point + 4;
      }
    } else if (argv[start_point + 1] == 't') {
      atan_sign = tan_check(argv, start_point + 2);
      if (!atan_sign) {
        *point = start_point + 4;
      }
    } else {
      error_sign = 1;
    }
    if (!error_sign && (asinus_sign ^ acosinus_sign ^ atan_sign)) {
      error_sign = 1;
    }
  } else if (argv[start_point] == 'l' && start_point < length) {
    if (argv[start_point + 1] == 'o') {
      log_sign = log_check(argv, start_point + 2);
      if (!log_sign) {
        *point = start_point + 3;
      }
    } else if (argv[*point + 1] == 'n') {
      *point = start_point + 2;
      error_sign = in_brackets_check(argv, *point);
    } else {
      error_sign = 1;
    }
  } else if (argv[start_point] == 'm' && start_point < length) {
    error_sign = mod_check(argv, start_point + 1);
    if (!error_sign) {
      *point = start_point + 3;
    }
  } else if (argv[start_point] == 'p' && start_point < length) {
    if (argv[start_point + 1] != 'i') {
      error_sign = 1;
    }
    if (!error_sign) {
      *point = start_point + 2;
    }
  } else {
    error_sign = 1;
  }
  return error_sign;
}

int string_check(char *argv) {
  int error_sign = 0;
  int length = strlen(argv);
  char number_string[] = "1234567890x.";
  char sign_string[] = "+-*/^";
  char x[] = "x";
  char function_string[] = "sctalmp";
  char check_legal[] = "odins)(";
  for (int i = 0; i < length - 1; i++) {
    if (!strchr(number_string, argv[i]) && !strchr(sign_string, argv[i]) &&
        !strchr(x, argv[i]) && !strchr(function_string, argv[i]) &&
        !strchr(check_legal, argv[i]))
      error_sign = 1;
  }
  for (int i = 0; i < length; i++) {
    if (argv[i] == '(') {
      error_sign = check_brackets(argv);
    }
  }
  if (strchr(sign_string, length - 1)) {
    error_sign = 1;
  } else {
    for (int i = 0; i < length; i++) {
      if (strchr(sign_string, argv[i]) &&
          (strchr(sign_string, argv[i + 1]) || argv[i + 1] == '.')) {
        error_sign = 1;
      }
      if (argv[i] == '.' &&
          (!strchr(number_string, argv[i + 1]) || argv[i + 1] == '.' ||
           argv[i + 1] == 'x' || argv[i + 1] == '\0')) {
        error_sign = 1;
      }
      if (argv[i] == 'x' && strchr(number_string, argv[i + 1]) &&
          argv[i + 1] != '\0') {
        error_sign = 1;
      }
    }
  }
  if (!error_sign) {
    for (int i = 0; i < length; i++) {
      if (strchr(number_string, argv[i]) == NULL &&
          strchr(sign_string, argv[i]) == NULL && argv[i] != ')' &&
          argv[i] != '(' && strchr(function_string, argv[i])) {
        error_sign = function_check(argv, &i);
        if (error_sign) {
          break;
        }
      }
    }
  }
  if (!error_sign) {
    for (int i = 0; i < length; i++) {
      if (strchr(x, argv[i])) {
        error_sign = 2;
        break;
      }
    }
  }

  return error_sign;
}

int check_brackets(char *argv) {
  int bracket_left = 0;
  int bracket_right = 0;
  int error_sign = 0;
  char string_sign[] = "+-*/^";
  int length = strlen(argv);
  for (int i = 0; i < length; i++) {
    if (argv[i] == '(') {
      bracket_left++;
      if (bracket_left < bracket_right)
        error_sign = 1;
    }
    if (argv[i] == ')') {
      bracket_right++;
      if (i > 0) {
        if (strchr(string_sign, argv[i - 1])) {
          error_sign = 1;
        }
      }
    }
  }
  if (bracket_left != bracket_right) {
    error_sign = 1;
  }
  return error_sign;
}
int sinus_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'n') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int sqrt_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'r') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 't') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int cosinus_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'o') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 's') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (!error_mark) {
    error_mark = in_brackets_check(argv, index);
  }
  return error_mark;
}

int tan_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'a') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 'n') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int log_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'g') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int mod_check(char *argv, int index) {
  int error_mark = 0;
  char sign_string[] = "+-*/^.";
  if (index == 1) {
    error_mark = 1;
  } else if (strchr(sign_string, argv[index - 2])) {
    error_mark = 1;
  }
  if (argv[index] != 'o') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 'd') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (strchr(sign_string, argv[index])) {
    error_mark = 1;
  }
  return error_mark;
}
int in_brackets_check(char *argv, int index) {
  int error_mark = 0;
  char number_string[] = "1234567890x.";
  char sign_string[] = "+-*/^";
  char function_string[] = "sctalm";
  if (argv[index] != '(') {
    error_mark = 1;
  }
  if (!error_mark) {
    if (index != '\0') {
      index++;
    }
    if (strchr(number_string, argv[index]) ||
        strchr(sign_string, argv[index]) ||
        strchr(function_string, argv[index]) || argv[index] == '(') {
      while (strchr(number_string, argv[index]) ||
             strchr(sign_string, argv[index]) ||
             strchr(function_string, argv[index]) || argv[index] == '(') {
        if (strchr(function_string, argv[index])) {
          error_mark = function_check(argv, &index);
        } else {
          index++;
        }
      }
    } else {
      error_mark = 1;
    }
    if (strchr(sign_string, argv[index - 1])) {
      error_mark = 1;
    }
    if (argv[index] != ')') {
      error_mark = 1;
    }
    if (argv[index] == '\0') {
      error_mark = 1;
    }
  }
  return error_mark;
}

result credit_res(double sum, int time, double percent, int mode) {
  result res = {0};
  double i = percent / 12 / 100;
  time *= 12;
  // printf("i = %f\n", i);
  if (!mode) {
    double k = i / (1 - pow(1 + i, -time));
    // double g = pow(1 + i, time);
    // printf("g = %f\n", g);
    // double v = g - 1;
    // printf("v = %f\n", v);
    // double k = i / v;
    // printf("k = %f\n", k);
    res.monthly_payment_max = k * sum;
    res.all_payment = k * sum * time;
    res.overpayment = sum * (k * time - 1);
    // res.monthly_payment_max = sum * (k * time - 1);
  } else {
    double main = sum / time;
    res.monthly_payment_max = main + sum * i;
    res.monthly_payment_min = main + main * i;
    res.overpayment = i * sum * (time + 1) / 2.;
    res.all_payment = res.overpayment + sum;
  }
  return res;
}

size_t s21_strlcpy(char *dst, const char *src, size_t maxlen) {
  const size_t srclen = strlen(src);
  if (srclen + 1 < maxlen) {
    memcpy(dst, src, srclen + 1);
  } else if (maxlen != 0) {
    memcpy(dst, src, maxlen - 1);
    dst[maxlen - 1] = '\0';
  }
  return srclen;
}

void free_stack(element *pHead) {
  element *pNode = pHead, *pNext;

  while (NULL != pNode) {
    pNext = pNode->next;
    free(pNode);
    pNode = pNext;
  }
}

void set_x_value(double value, element *final) {
  element *lexeme_buffer = final;

  while (lexeme_buffer) {
    if (lexeme_buffer->type == X) {
      lexeme_buffer->value = value;
    }
    lexeme_buffer = lexeme_buffer->next;
  }
}
