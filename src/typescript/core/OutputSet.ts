import { MemberProperties } from "./MemberProperties"

enum OutputSetBaseSelector{
    All
};

export type OutputSetSelector = OutputSetBaseSelector | string[]; 

export type OutputSet = {
    readonly properties: MemberProperties
    readonly selectors: OutputSetSelector[],
}