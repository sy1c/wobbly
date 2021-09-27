#define ENCL_XOR PD3
#define ENCL_B PE2
#define ENCR_XOR PD2
#define ENCR_B PE3

volatile uint8_t left_A, left_B, right_A, right_B;
volatile uint16_t left_count, right_count;

void encoders_init(void);
int16_t encoders_left_counts(void);
int16_t encoders_right_counts(void);