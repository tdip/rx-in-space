import { QuerySet, QueryArgs } from "./QueryArgs";
import { OptionalSelector, RequiredSelector, QueryProperty } from "./QueryProperties";
import { OutputSet, OutputSetAtom } from "./UpdateArgs";

export namespace Utils{

    export namespace OutputSet{

        export function isOptional(atom: OutputSetAtom): atom is OptionalSelector{
            return atom && (<OptionalSelector>atom).optional && true;
        }

        export function isRequired(atom: OutputSetAtom): atom is RequiredSelector{
            return atom && (<RequiredSelector>atom).required && true;
        }

        export function getQueryProperty(atom: OutputSetAtom): QueryProperty{
            if(isOptional(atom)){
                return atom.optional;
            }

            if(isRequired(atom)){
                return atom.required;
            }

            throw new Error(`Unknown atom type "${JSON.stringify(atom)}"`);
        }
    }

    export function asRequiredSet(query: QuerySet): OutputSet {
        const keys = Object.keys(query);
        const result: OutputSet = {};

        keys.forEach(key => {
            const required = query[key];
            result[key] = { required };
        });

        return result;
    }

    export function asQuerySet(output: OutputSet): QuerySet{
        
        const result: QuerySet = {};
        Object.keys(output).forEach(
            (key) => {
                const outputEntry = output[key];
                result[key] = OutputSet.getQueryProperty(outputEntry);
            });

        return result;
    }

    export function addKeys(args: QueryArgs<any>, query: QuerySet): QueryArgs<any>{
        return {
            mergeStrategy: args.mergeStrategy,
            type: args.type,
            query: {...args.query, ...query}
        };
    }
}