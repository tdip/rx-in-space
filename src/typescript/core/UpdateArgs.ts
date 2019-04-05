import { Observable } from "rxjs"

import { ISignalsLink } from "./ISignalsLink"
import { QueryArgs } from "./QueryArgs"
import { OptionalSelector, RequiredSelector } from "./QueryProperties"

export type OutputSetAtom = OptionalSelector | RequiredSelector;

export type OutputSet = {
    [key: string]: OutputSetAtom
}

/**
 * Combination of a stream of values and the
 * set where the values will be inserted
 * in the reactive graph.
 */
export type SetValue = {
    values: Observable<any>,
    key: OutputSet
}

/**
 * Operation that joins two values
 * in the signals reactive graph
 */
export type LinkValues = {
    readonly source: QueryArgs<any>[],
    readonly link: ISignalsLink,
    readonly destination: OutputSet[]
}

export type Template = {
    readonly control: OutputSet,
    readonly source: QueryArgs<any>[]
}

export type LinkValuesOption = { readonly link: LinkValues }

export type SetValueOption = { readonly setValue: SetValue }

export type TemplateOption = { readonly template: Template }

export type Update = SetValueOption | LinkValuesOption | TemplateOption;

export type UpdateArgs = {
    readonly updates: Update[]
}