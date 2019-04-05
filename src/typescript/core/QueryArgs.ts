import { QueryProperty } from "./QueryProperties"

export namespace MergeStrategy{
    export type Aggregate = {
        aggregate: {
            groupKeys?: string[]
        }
    };

    export const Concat = "concat";

    export type Type = "sequence" | "concat" | Aggregate ;

    export const Sequence: Type = "sequence";

    export function Aggregate(groupKeys?: string[]): Aggregate {
        return { aggregate: { groupKeys }}
    }
}

export type MergeStrategy = MergeStrategy.Type;

export type QueryType<T> = {}

export type QuerySet = {
    [key: string]: QueryProperty
}

export type QueryArgs<T> = {
    readonly query: QuerySet,
    readonly type: QueryType<T>,
    readonly mergeStrategy: MergeStrategy
}
