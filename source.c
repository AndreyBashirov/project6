#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define eps 0.001
int num_of_iterations = 0;
//num of iterations
double f1(double x)
{
    return (3 * (0.5/ (x + 1) + 1));
};
double f2(double x)
{
    return (2.5 * x - 9.5);
};
double f3(double x)
{
    return 5 / x;
};

double root(double L, double R, double (*func1) (double), double (*func2) (double), double eps1) //find root between two functions(f1 - f2 = 0)
{
    double x;
    int sign = 1;
    while(R - L >= eps1)
    {
        num_of_iterations++;
        x = (L + R)/ 2;
        if(sign * (func1(L) - func2(L)) > sign * (func1(R) - func2(R))) sign *= -1;
        if ((sign * (func1(x) - func2(x))) > 0) R = x;
        else L = x;
    }
    return L;
}

double trapecsum(double x1, double x2, double (*func) (double), int n)  //calculating integral
{
    double height = (x2 - x1) / n;
    double sum = 0;
    for(int i = 0; i < n; ++i)
    {
        double half = (func(x1 + i * height) + func(x1 + (i + 1) * height)) / 2;
        sum += height * half;
    }
    return sum;
}

double integral(double x1, double x2, double (*func) (double), double eps2)  //finding integral with set precision
{
    int n = 100;
    double sum1 = trapecsum(x1, x2, func, n);
    n *= 2;
    double sum2 = trapecsum(x1, x2, func, n);
    while(fabs(sum1 - sum2) / 3 >= eps2)
    {
        sum1 = sum2;
        n *= 2;
        sum2 = trapecsum(x1, x2, func, n);
    }
    return sum1;
}

//Sample
double f4(double x)
{
    return (9 - (x - 3) * (x - 3));
}

double f5(double x)
{
    return (x - 3);
}

double f6(double x)
{
    return (3 - x);
}

double (*functions[6])(double) = {&f1, &f2, &f3, &f4, &f5, &f6};    //an array of functions

void print_del(void){
    printf("------------------------------------------------------\n");
}

void print_roots(void){     //shows the points of intersection
    double root1 = root(0,6, f1, f3, eps);
    double root2 = root(0,6, f1, f2, eps);
    double root3 = root(0,6, f2, f3, eps);
    print_del();
    printf("root f1, f3: %lf\nroot f1, f2: %lf\nroot f2, f3: %lf\n", root1, root2, root3);
    print_del();
}

void print_integrals(void){     //prints integrals of main
    double root1 = root(0,6, f1, f3, eps);
    double root2 = root(0,6, f1, f2, eps);
    double root3 = root(0,6, f2, f3, eps);
    double I_f1 = integral(root1, root2, f1, eps);
    double I_f2 = integral(root3, root2, f2, eps);
    double I_f3 = integral(root1, root3, f3, eps);
    print_del();
    printf("integral f1: %lf\nintegral f2: %lf\nintegral f3: %lf\n", I_f1, I_f2, I_f3);
    print_del();
}

void print_iters(int num_a, int num_b, double a, double b){     //prints the number of iterations to find the root of (f1-f2 = 0, f2 - f3 = 0, f1 - f3 = 0)
    num_of_iterations = 0;
    double root1 = root(0,6, f1, f3, eps);
    double num_of_iterations1 = num_of_iterations;
    num_of_iterations = 0;
    double root2 = root(0,6, f1, f2, eps);
    double num_of_iterations2 = num_of_iterations;
    num_of_iterations = 0;
    double root3 = root(0,6, f2, f3, eps);
    double num_of_iterations3 = num_of_iterations;
    num_of_iterations = 0;
    print_del();
    printf("iters for root f1, f3: %lf\niters for root f1, f2: %lf\niters for root f2, f3: %lf\n", num_of_iterations1, num_of_iterations2, num_of_iterations3);
    print_del();
}

void print_answer(void){        //prints the area of the shape between the curves
    double root1 = root(0,6, f1, f3, eps);
    double root2 = root(0,6, f1, f2, eps);
    double root3 = root(0,6, f2, f3, eps);
    double I_f1 = integral(root1, root2, f1, eps);
    double I_f2 = integral(root3, root2, f2, eps);
    double I_f3 = integral(root1, root3, f3, eps);
    double ans = I_f1 - I_f2 - I_f3;
    print_del();
    printf("answer: %lf\n", ans);
    print_del();
}

void test_roots(int num_a, int num_b, double a, double b){      //shows the point of intersection of two functions
    double cur_root = root(a,  b, functions[num_a], functions[num_b], eps);
    print_del();
    printf("intersection of f%d and f%d on [%lf, %lf] segment: %lf \n", num_a + 1, num_b + 1, a, b, cur_root);
    print_del();
}

void test_integrals(int num, double a, double b){       //calculate the integral on section
    double cur_integral = integral(a, b, functions[num], eps);
    print_del();
    printf("value of integral of f%d on [%lf, %lf] segment: %lf \n", num + 1, a, b, cur_integral);
    print_del();
}

void print_help_info(void){     //-help
    print_del();
    printf("realised functions:\n");
    printf("f1: y = 3 * (1 / (2 * (x + 1)) + 1)");
    printf("f2: y = 2.5 * x - 9.5");
    printf("f3: y = 5/x");
    printf("(for tests) f4: y = (9 - (x - 3) * (x - 3))");
    printf("(for tests) f5: y = (x - 3)");
    printf("(for tests) f6: y = (3 - x)");
    print_del();
    printf("to view intersection points use flag: -roots\n");
    printf("to view value of integral on segment between roots use flag: -intergals\n");
    printf("to view answer use flag: -answer\n");
    printf("to view help information use flag: -help\n");
    printf("to view number of iterations you need to use: -iters \n");
    printf("borders for functions from task:\n");
    printf("f1, f2: [ 0 , 6 ] \n");
    printf("f1, f3: [ 0 , 6 ] \n");
    printf("f2, f3: [ 0 , 6 ] \n");
    printf("to find intersection of functions use: -test-roots <number of first func> <number of second func> <left border> <right border>\n");
    printf("to calculate integral on segment use: -test-integrals <number of function> <left border> <right border>\n");
    print_del();
}

void print_exeption(void){
    print_del();
    printf("you have used incorrect arguments of command line.\n Please use -help to check list of supported commands\n ");
    print_del();
}

int main (int argc, char ** argv) {
    int num_of_commands = 7;
    char * commands[] = {"-roots", "-integrals", "-answer", "-help", "-iters", "-test-roots" ,"-test-integrals"};//list of commands
    int  cur_arg = 1;

    while (cur_arg < argc){//processing command line arguments
        int cur_num = 0;
        for (int i = 0; i < num_of_commands; i++){//correlate an argument with its number for switch operation
            if (strcmp(argv[cur_arg], commands[i]) == 0){
                cur_num = i + 1;
            }
        }
        int f_a, f_b;
        double a, b;
        switch (cur_num)
        {
        case 1: //print roots of the task
            print_roots();
            break;

        case 2: //print integrals of the task
            print_integrals();
            break;

        case 3://print answer on task
            print_answer();
            break;

        case 4: //list of commands
            print_help_info();
            break;
        case 5: // count the iterations for calculating root
            print_iters(f_a, f_b, a, b);
            break;
        case 6://find the point of intersection between two functions
            f_a = atoi(argv[cur_arg + 1]), f_b = atoi(argv[cur_arg + 2]);
            a = atof(argv[cur_arg + 3]), b = atof(argv[cur_arg + 4]);
            f_a--;
            f_b--;
            cur_arg += 4;
            test_roots(f_a, f_b, a, b);
            break;
        case 7://calculate the integral of function on the section
            f_a = atoi(argv[cur_arg + 1]);
            a = atof(argv[cur_arg + 2]), b = atof(argv[cur_arg + 3]);
            f_a--;
            cur_arg += 3;
            test_integrals(f_a, a, b);
            break;
        default:
        print_exeption(); //wrong command
            break;
        }
        cur_arg++;
    }
    return 0;
}
