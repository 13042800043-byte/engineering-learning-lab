#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

enum
{
    highTaskTargetRuns = 4,
    lowTaskTargetRuns = 3
};

static volatile uint32_t highTaskRuns = 0;
static volatile uint32_t lowTaskRuns = 0;

static void highPriorityTask(void *parameters)
{
    const char *taskName = (const char *)parameters;

    for (;;)
    {
        ++highTaskRuns;
        printf("[%s] run %lu -> delay 300 ms (Running -> Blocked)\n",
               taskName,
               (unsigned long)highTaskRuns);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
static void lowPriorityTask(void *parameters)
{
    const char *taskName = (const char *)parameters;

    for (;;)
    {
        ++lowTaskRuns;
        printf("[%s] run %lu -> delay 500 ms (Running -> Blocked)\n",
               taskName,
               (unsigned long)lowTaskRuns);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void monitorTask(void *parameters)
{
    (void)parameters;

    for (;;)
    {
        if ((highTaskRuns >= highTaskTargetRuns) &&
            (lowTaskRuns >= lowTaskTargetRuns))
        {
            puts("LAB PASS: both tasks reached their target counts");
            exit(EXIT_SUCCESS);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main(void)
{
    BaseType_t result;

    setvbuf(stdout, NULL, _IONBF, 0);
    puts("LAB START");
    puts("HIGH priority=2, LOW priority=1, MONITOR priority=3");

    result = xTaskCreate(
        highPriorityTask,
        "HIGH",
        configMINIMAL_STACK_SIZE,
        (void *)"HIGH",
        2,
        NULL);

    if (result != pdPASS)
    {
        fputs("Failed to create HIGH task.\n", stderr);
        return EXIT_FAILURE;
    }

    result = xTaskCreate(
        lowPriorityTask,
        "LOW",
        configMINIMAL_STACK_SIZE,
        (void *)"LOW",
        1,
        NULL);

    if (result != pdPASS)
    {
        fputs("Failed to create LOW task.\n", stderr);
        return EXIT_FAILURE;
    }

    result = xTaskCreate(
        monitorTask,
        "MONITOR",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        NULL);

    if (result != pdPASS)
    {
        fputs("Failed to create MONITOR task.\n", stderr);
        return EXIT_FAILURE;
    }

    vTaskStartScheduler();

    fputs("Scheduler stopped unexpectedly.\n", stderr);
    return EXIT_FAILURE;
}

void vApplicationMallocFailedHook(void)
{
    fputs("FreeRTOS heap allocation failed.\n", stderr);
    exit(EXIT_FAILURE);
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *taskName)
{
    (void)task;
    fprintf(stderr, "Stack overflow in task: %s\n", taskName);
    exit(EXIT_FAILURE);
}

void vAssertCalled(const char *file, int line)
{
    fprintf(stderr, "FreeRTOS assertion failed at %s:%d\n", file, line);
    exit(EXIT_FAILURE);
}
