#include "../include/processor.hpp"

processor::processor() {
    this->mem = memory(_big, _hex, _hex);
    this->b_reg = registers();
}

processor::~processor() {
    this->mem.~memory();
    this->b_reg.~registers();
}

void processor::fetch() {
    if(b_reg.PC < BASE_DATA_ADDRESS) {
        b_reg.RI = (uint32_t) mem.lw(b_reg.PC, 0);
        b_reg.PC += _word;
    }
    else
        throw out_of_range(PC_OUT_OF_BOUNDS);
}

void processor::decode() {
    this->inst_fields.opcode = (uint8_t)(b_reg.RI>>26);
    this->inst_fields.rs = (uint8_t)((b_reg.RI>>21) & 0x0000001F);
    this->inst_fields.rt = (uint8_t)((b_reg.RI>>16) & 0x0000001F);
    this->inst_fields.rd = (uint8_t)((b_reg.RI>>11) & 0x0000001F);
    this->inst_fields.shammt = (uint8_t)((b_reg.RI>>6) & 0x0000001F);
    this->inst_fields.funct = (uint8_t)((b_reg.RI) & 0x0000003F);
    this->inst_fields.k16 = (int16_t) (b_reg.RI & 0x0000FFFF);
    this->inst_fields.k26 = (uint32_t) (b_reg.RI & 0x03FFFFFF);
}

void processor::execute() {
    switch (this->inst_fields.opcode){
        case EXT:
            switch (this->inst_fields.funct){
                case ADD:
                    break;
                case SUB:
                    break;
                case MULT:
                    break;
                case DIV:
                    break;
                case AND:
                    break;
                case OR:
                    break;
                case XOR:
                    break;
                case NOR:
                    break;
                case SLT:
                    break;
                case JR:
                    break;
                case SLL:
                    break;
                case SRL:
                    break;
                case SRA:
                    break;
                case SYSCALL:
                    break;
                case MFHI:
                    break;
                case MFLO:
                    break;
                default:
                    throw logic_error(UNKNOWN_OPCODE);
            }
        case LW:
            break;
        case LB:
            break;
        case LBU:
            break;
        case LH:
            break;
        case LHU:
            break;
        case LUI:
            break;
        case SW:
            break;
        case SB:
            break;
        case SH:
            break;
        case BEQ:
            break;
        case BNE:
            break;
        case BLEZ:
            break;
        case BGTZ:
            break;
        case ADDI:
            break;
        case SLTI:
            break;
        case SLTIU:
            break;
        case ANDI:
            break;
        case ORI:
            break;
        case XORI:
            break;
        case J:
            break;
        case JAL:
            break;
        default:
            throw logic_error(UNKNOWN_OPCODE);
    }
}
