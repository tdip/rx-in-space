import { Observable } from "rxjs";

import { QueryArgs } from "./QueryArgs"
import { UpdateArgs } from "./UpdateArgs"

export interface ISignalsCore{
    query<T>(query: QueryArgs<T>): Observable<T>;
    update(values: UpdateArgs);
}